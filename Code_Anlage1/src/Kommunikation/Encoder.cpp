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
#include "../../header/PulseCodes.h"
#include "../../header/ChannelUtils.h"
#include "../../header/ADC_Sources/ADC.h"

static unsigned int previousDatainReg = 0;
int beltMin = 3600;
int beltMax = 0;
int defaultHight = 0;
int flatMin = 60000;
int flatMax = 2560;


void encoderThread(int channelID_Encoder, int connectionID_Dispatcher){
	ThreadCtl(_NTO_TCTL_IO, 0);
    bool calibration_mode = true;

	uintptr_t gpioBase = mmap_device_io(GPIO_LENGTH, GPIO_BANK_0);
    previousDatainReg = in32(uintptr_t(gpioBase + GPIO_DATA_IN));

	_pulse msg;
	bool receiveRunning = true;

	while(receiveRunning){
     	int recvid = myReceivePulse(channelID_Encoder, &msg);
		if (recvid > 0) {
			continue;
		}
        switch(msg.code) {
            case PULSE_STOP_THREAD:
                printf("Encoder Thread kill code received!\n");
                receiveRunning = false;
                break;
            case PULSE_GPIO:
                encodeAndSendMsg(msg.value.sival_int, connectionID_Dispatcher);
                break;
            case PULSE_CALIBRATION_OPERATION:
                if (msg.value.sival_int) { // == 1
                    calibration_mode = true;
                } else { // == 0
                    calibration_mode = false;
                }
                break;
            case PULSE_HIGHT:
                if(calibration_mode){
                    calibrationMode(msg, connectionID_Dispatcher);
                }else{
                    operationMode(msg, connectionID_Dispatcher);
                }
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
				MsgSendPulse(connectionID_Dispatcher, -1, PULSE_LOW_HIGH_MACHINE1, message);


			} else { // von 1 auf 0

				int message = pinsOfInterest[pin];
				MsgSendPulse(connectionID_Dispatcher, -1, PULSE_HIGH_LOW_MACHINE1, message);

			}
		}

	}
	previousDatainReg = currentDatainReg;
}

void operationMode(_pulse msg, int connectionID_Dispatcher) {
    int hight = msg.value.sival_int;
    static bool measuring_wp = false;
    static int maxHight = 1000000;
    static int last = 0;

    if(!measuring_wp && (beltMax > hight) && (hight > beltMin)) {
    	if(last != 0){
    		printf("ENCODER: BELT!!\n");
    		last = 0;
    	}
        return;
    }
    if(!measuring_wp && (hight < beltMin)){
        MsgSendPulse(connectionID_Dispatcher, -1, PULSE_HIGHT, 10000);
        measuring_wp = true;
    }
    if(measuring_wp && (hight < beltMin) && (hight < maxHight)){
        maxHight = hight;
    }
    if(measuring_wp && (beltMax > hight) && (hight > beltMin)){
        if(flatMax > maxHight && maxHight > flatMin){
            MsgSendPulse(connectionID_Dispatcher, -1, PULSE_HIGHT, 1); // Flat
            if(last != 1){
				printf("ENCODER: FLAT!!\n");
				last = 1;
			}
        }else{
        	if(!(flatMax > maxHight)){
        		printf("ENCODER: hight zu kurz\n");
        	} else if(!(maxHight > flatMin)){
        		printf("ENCODER: hight zu gross\n");
        	}
            MsgSendPulse(connectionID_Dispatcher, -1, PULSE_HIGHT, 2); // not flat
            if(last != 2){
				printf("ENCODER: NOT FLAT!!\n");
				last = 2;
			}
        }

        measuring_wp = false;
        maxHight = 1000000;
    }
}


void calibrationMode(_pulse msg, int connectionID_Dispatcher){
    int hight = msg.value.sival_int;
    static bool hightchanged = false;

    if (!hightchanged && ((beltMax - hight) > 200)){
        MsgSendPulse(connectionID_Dispatcher, -1, PULSE_HIGHT, 10000);
        hightchanged = true;
    }

    if(hightchanged && (beltMax > hight) && (hight > beltMin)){
    	MsgSendPulse(connectionID_Dispatcher, -1, PULSE_HIGHT, 10000);
    	hightchanged = false;
    }

    if(!hightchanged && (beltMax < hight)){
		beltMax = hight;
		beltMin = beltMax - 200;
        //printf("ENCODER: beltMin: %d, beltMax: %d\n", beltMin, beltMax);
	}

    if(flatMin > hight){
        flatMin = hight - 25;
        flatMax = flatMin + 200;
        //printf("ENCODER: flatMin: %d, flatMax: %d\n", flatMin, flatMax);
    }
}
