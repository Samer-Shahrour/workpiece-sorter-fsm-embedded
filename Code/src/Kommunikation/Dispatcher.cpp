#include <bitset>
#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/mman.h>
#include <hw/inout.h>
#include <string>
#include "../../header/Kommunikation/Encoder.h"
#include "../../header/Kommunikation/Dispatcher.h"
#include "../../header/hal/Sensors.h"
#include "../../header/PulseCodes.h"
#include "../../header/ChannelUtils.h"

//static void (*decodeFunktions[20])(); // = { func1, func2, func3, ... , func20} ;

unsigned int previousDatainReg = 0;

int dispatcherThread(int* channelID_Dispatcher){
	ThreadCtl(_NTO_TCTL_IO, 0);

	_pulse msg;
	bool receiveRunning = true;
	while(receiveRunning){
		printf("dispatcher receiving!\n");
        int recvid = myReceivePulse(*channelID_Dispatcher, &msg);
		printf("dispatcher receiving %d %d!\n", msg.code, msg.value.sival_int);
		if (recvid == 0) {
			if (msg.code == PULSE_STOP_THREAD) {
				printf("Dispatcher Thread kill code received!\n");
				receiveRunning = false;
			} else if (msg.code == PULSE_LOW_HIGH_MACHINE1) { // von anlage1
				decodeMsg(msg.value.sival_int);
				printf("Dispatcher: etwas L %d!\n", msg.value.sival_int);
			} else if (msg.code == PULSE_HIGH_LOW_MACHINE1) { //
				printf("Dispatcher: etwas H %d!\n", msg.value.sival_int);
			}
		}
	}
	return EXIT_SUCCESS;
}

void decodeMsg(int msg) {

}


