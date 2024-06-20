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
#include "../header/Hal/ADCThread.h"
#include "../header/PulseCodes.h"
#include "../header/ChannelUtils.h"
#include "../header/FSMs/E_STOP/ContextEStop.h"
#include "../header/FSMs/FSMThread.h"
#include "../header/logger.h"


int main(int argc, char** args);

using namespace std;

int main(int argc, char** args) {
    ThreadCtl(_NTO_TCTL_IO, 0);
    system("gns -s");

    int channelID_Encoder = myCreateChannel();
    int channelID_Dispatcher = myCreateChannel();
    int channelID_ISR = myCreateChannel();
    int channelID_HalActuators = myCreateChannel();
    int channelID_FSM_ESTOP = myCreateChannel();
    int channelID_FSM = myCreateChannel();
    int channelID_Logger = myCreateChannel();


    int connectionID_Encoder = myConnectAttach(channelID_Encoder);
    int connectionID_Dispatcher = myConnectAttach(channelID_Dispatcher);
    int connectionID_ISR = myConnectAttach(channelID_ISR);
    int connectionID_HalActuators = myConnectAttach(channelID_HalActuators);
    int connectionID_FSM_ESTOP = myConnectAttach(channelID_FSM_ESTOP);
    int connectionID_FSM = myConnectAttach(channelID_FSM);
    int connectionID_Logger = myConnectAttach(channelID_Logger);


    initInterrupt(connectionID_ISR);

    /* Start threads*/
    thread receivingThread = thread(&interruptThread, channelID_ISR, connectionID_Encoder);
    thread encoderT = thread(&encoderThread, channelID_Encoder, connectionID_Dispatcher);
    thread dispatcherT = thread(&dispatcherThread, channelID_Dispatcher, connectionID_FSM_ESTOP, connectionID_FSM, connectionID_HalActuators, connectionID_Encoder, connectionID_Logger);
    thread threadAdc = thread(&threadADC, connectionID_Encoder);
    thread serverT = thread(&server, connectionID_Dispatcher);
    thread actuatorsT = thread(&actuatorsThread, connectionID_HalActuators, channelID_HalActuators);
    thread fsmT = thread(&FSM_Thread, channelID_FSM, connectionID_FSM, connectionID_Dispatcher);
    thread loggerT = thread(&loggerThread, channelID_Logger);

    while(true);


    receivingThread.join();
    encoderT.join();
    dispatcherT.join();
    threadAdc.join();
    serverT.join();
    actuatorsT.join();
    fsmT.join();
    loggerT.join();

    return EXIT_SUCCESS;
}

