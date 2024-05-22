#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/mman.h>
#include <hw/inout.h>
#include "../../header/Kommunikation/Encoder.h"
#include "../../header/hal/Sensors.h"
#include "../../header/hal/Actuators.h"
#include "../../header/Kommunikation/Encoder.h"
#include "../../header/PulseCodes.h"
#include "../../header/ChannelUtils.h"

static unsigned int previousDatainReg = 0;


int encoderThread(int* channelID_Encoder, int *channelID_Dispatcher){
	ThreadCtl(_NTO_TCTL_IO, 0);
	uintptr_t gpioBase = mmap_device_io(GPIO_LENGTH, GPIO_BANK_0);
    previousDatainReg = in32(uintptr_t(gpioBase + GPIO_DATA_IN));
    int connectionID_Dispatcher = myConnectAttach(*channelID_Dispatcher);
	_pulse msg;
	bool receiveRunning = true;
	while(receiveRunning){
      int recvid = myReceivePulse(*channelID_Encoder, &msg);
		if (recvid == 0) {
			if (msg.code == PULSE_STOP_THREAD) {
				printf("Dispatcher Thread kill code received!\n");
				receiveRunning = false;
			} else if (msg.code == PULSE_INTR_ON_PORT0_MACHINE1) { // von anlage1
				encodeAndSendMsg(msg.value.sival_int, &connectionID_Dispatcher);
			} else if (msg.code == PULSE_INTR_ON_PORT0_MACHINE2) { // von anlage2

			}
		}
	}
}

void encodeAndSendMsg(unsigned int currentDatainReg, int *connectionID_Dispatcher){
	for (int pin = 0; pin < 10; pin++) {
		bool currentLevel = (currentDatainReg & pinsOfInterest[pin]) != 0;
		bool previousLevel = (previousDatainReg & pinsOfInterest[pin]) != 0; // letzter zustand
		if(currentLevel != previousLevel) { // Pin wurde verändert
			if(currentLevel) { // von 0 auf 1
				int message = pinsOfInterest[pin];
				MsgSendPulse(*connectionID_Dispatcher, -1, PULSE_LOW_HIGH_MACHINE1, message);
				printf("Level-Interrupt on pin %d, Level HIGH\n", pin);
			} else { // von 1 auf 0
				int message = pinsOfInterest[pin];
				MsgSendPulse(*connectionID_Dispatcher, -1, PULSE_HIGH_LOW_MACHINE1, message);
				printf("Level-Interrupt on pin %d, Level LOW\n", pin);
			}
		}
	}
	previousDatainReg = currentDatainReg;
}
