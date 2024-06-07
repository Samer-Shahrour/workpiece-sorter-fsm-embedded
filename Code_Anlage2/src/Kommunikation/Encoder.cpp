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


void encoderThread(int channelID_Encoder, int connectionID_Dispatcher){
	ThreadCtl(_NTO_TCTL_IO, 0);

    int beltMin = 3600;
    int beltMax = 3690;

    int flatMin = 2440;
    int flatMax = 2560;


	uintptr_t gpioBase = mmap_device_io(GPIO_LENGTH, GPIO_BANK_0);
    previousDatainReg = in32(uintptr_t(gpioBase + GPIO_DATA_IN));

	_pulse msg;
	bool receiveRunning = true;
	while(receiveRunning){
     	int recvid = myReceivePulse(channelID_Encoder, &msg);
		if (recvid > 0) {
			continue;
		}
		switch(msg.code){
			case PULSE_STOP_THREAD:
				printf("Encoder Thread kill code received!\n");
				receiveRunning = false;
				break;

			case PULSE_GPIO:
				encodeAndSendMsg(msg.value.sival_int, connectionID_Dispatcher);
				break;

            case PULSE_HIGHT:
                // das ist der typ des wps
                int hight = msg.value.sival_int;

                if(beltMax > hight && hight > beltMin){
                    hight = 0;
                    //belt
                }
                else if(beltMin > hight && hight > flatMax){
                    hight = 1;
                    //side
                }
                else if(flatMax > hight && hight > flatMin){
                    hight = 2;
                    //flat
                }else{
                    hight = 3;
                }
                MsgSendPulse(connectionID_Dispatcher, -1, PULSE_HIGHT, hight);
                break;
		}
	}
	printf("Encoder Thread Done!\n");
}

void encodeAndSendMsg(unsigned int currentDatainReg, int connectionID_Dispatcher){
	for (int pin = 0; pin < 10; pin++) {
		bool currentLevel = (currentDatainReg & pinsOfInterest[pin]) != 0;
		bool previousLevel = (previousDatainReg & pinsOfInterest[pin]) != 0; // letzter zustand

		if(currentLevel != previousLevel) { // Pin wurde verändert
			if(currentLevel) { // von 0 auf 1

				int message = pinsOfInterest[pin];
				MsgSendPulse(connectionID_Dispatcher, -1, PULSE_LOW_HIGH_MACHINE2, message);


			} else { // von 1 auf 0

				int message = pinsOfInterest[pin];
				MsgSendPulse(connectionID_Dispatcher, -1, PULSE_HIGH_LOW_MACHINE2, message);

			}
		}

	}
	previousDatainReg = currentDatainReg;
}
