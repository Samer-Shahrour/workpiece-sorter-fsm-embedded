#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/mman.h>
#include <hw/inout.h>
#include <string>
#include "../../header/Kommunikation/Client.h"
#include "../../header/Kommunikation/Encoder.h"
#include "../../header/Kommunikation/Dispatcher.h"
#include "../../header/hal/Sensors.h"
#include "../../header/PulseCodes.h"
#include "../../header/ChannelUtils.h"
#include "../../header/Logik/Context.h"
#include "../../header/FSMs/E_STOP/ContextEStop.h"
#include <sys/dispatch.h>



unsigned int previousDatainReg = 0;

void dispatcherThread(int channelID_Dispatcher, int connectionID_FSM_ESTOP, int connectionID_FSM_HM, int connectionID_HAL_ACTUATORS){
	ThreadCtl(_NTO_TCTL_IO, 0);
	_pulse msg;
	bool receiveRunning = true;
	while(receiveRunning){
        int recvid = myReceivePulse(channelID_Dispatcher, &msg);
		if (recvid > 0) {
            continue;
        }
        switch(msg.code){
            case PULSE_STOP_THREAD:
                printf("Dispatcher Thread kill code received!\n");
                receiveRunning = false;
                break;

            case PULSE_LOW_HIGH_MACHINE1:
            case PULSE_HIGH_LOW_MACHINE1:
                MsgSendPulse(connectionID_FSM_ESTOP, -1, msg.code, msg.value.sival_int);
                break;


            case PULSE_LOW_HIGH_MACHINE2:
            case PULSE_HIGH_LOW_MACHINE2:
                MsgSendPulse(connectionID_FSM_ESTOP, -1, msg.code, msg.value.sival_int);
                if(msg.value.sival_int == E_STOP || msg.value.sival_int == BUTTON_RESET){ //send to A2
                   client(msg);
                }
                break;

            case PULSE_HIGHT:
                MsgSendPulse(connectionID_FSM_HM, -1, msg.code, msg.value.sival_int);
            	break;

            case PULSE_FROM_FSM_TO_HAL:
                MsgSendPulse(connectionID_HAL_ACTUATORS, -1, msg.code, msg.value.sival_int);
                break;

            case PULSE_FLASH_ON:
            case PULSE_FLASH_OFF:
                MsgSendPulse(connectionID_HAL_ACTUATORS, -1, msg.code, msg.value.sival_int);
                break;


        }
	}
	printf("Dispatcher Thread Done!\n");
}

