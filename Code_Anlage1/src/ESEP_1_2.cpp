#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/mman.h>
#include <hw/inout.h>

#include "../header/Kommunikation/Encoder.h"
#include "../header/Kommunikation/Dispatcher.h"
#include "../header/Kommunikation/Server.h"

#include "../header/Hal/Sensors.h"
#include "../header/Hal/Actuators.h"
#include "../header/Hal/InterruptReceiver.h"
#include "../header/logik/context.h"
#include "../header/Logik/ContextHeightMeasurement.h"

#include "../header/PulseCodes.h"
#include "../header/ChannelUtils.h"
#include "../header/FSMs/E_STOP/ContextEStop.h"




#define DEMO true			// true fÃ¼r Demozwecke, false fÃ¼r Dauerschleife
#define DEMO_DURATION 3		// Dauer der Demo in Minuten






int main(int argc, char** args);

using namespace std;

int main(int argc, char** args) {

    ThreadCtl(_NTO_TCTL_IO, 0);
    system("gns -s");


    int channelID_Encoder = myCreateChannel();
    int channelID_Dispatcher = myCreateChannel();
    int channelID_ISR = myCreateChannel();
    int channelID_HalActuators = myCreateChannel();
    int channelID_FSM_Hight_Measurement = myCreateChannel();
    int channelID_FSM_ESTOP = myCreateChannel();


    int connectionID_Encoder = myConnectAttach(channelID_Encoder);
    int connectionID_Dispatcher = myConnectAttach(channelID_Dispatcher);
    int connectionID_ISR = myConnectAttach(channelID_ISR);
    int connectionID_HalActuators = myConnectAttach(channelID_HalActuators);
    int connectionID_FSM_Hight_Measurement = myConnectAttach(channelID_FSM_Hight_Measurement);
    int connectionID_FSM_ESTOP = myConnectAttach(channelID_FSM_ESTOP);


    initInterrupt(connectionID_ISR);

    /* Start threads */
    thread receivingThread = thread(&interruptThread, channelID_ISR, connectionID_Encoder);
    thread encoderT = thread(&encoderThread, channelID_Encoder, connectionID_Dispatcher);
    thread dispatcherT = thread(&dispatcherThread, channelID_Dispatcher, connectionID_FSM_ESTOP, connectionID_FSM_Hight_Measurement, connectionID_HalActuators);
    //thread threadAdc = thread(&threadADC, channelID_FSM_Hight_Measurement, connectionID_Encoder);
    thread estopT = thread(&EStop_FSM_Thread, channelID_FSM_ESTOP, connectionID_Dispatcher);
    thread serverT = thread(&server, connectionID_Dispatcher);
    thread actuatorsT = thread(&actuatorsThread, connectionID_HalActuators, channelID_HalActuators);

    /* Waiting for demo */
    if (DEMO) {
        printf("Demo time for %d minutes...\n", DEMO_DURATION);
        this_thread::sleep_for(chrono::hours(DEMO_DURATION));
        printf("Stopping in...\n");
        for (int i = 1; i < 4 ; ++i) {
            printf("%d\n",i);
            this_thread::sleep_for(chrono::seconds(1));
        }
        printf("NOW!\n");
    } else {
        while (true) {
            this_thread::sleep_for(chrono::hours(999999));
        }
    }

    /* Clean up */
    int interruptID; //TODO: REMOVE
    int intr_detach_status = InterruptDetach(interruptID);
    if (intr_detach_status != EOK) {
        perror("Detaching interrupt failed!");
        exit(EXIT_FAILURE);
    }

    //MsgSendPulse(conID, -1, PULSE_STOP_THREAD, 0);
    receivingThread.join();
    encoderT.join();
    dispatcherT.join();

    return EXIT_SUCCESS;
}

