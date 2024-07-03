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
#include "../../header/variables.h"
#include "../../header/FSMs/E_STOP/ContextEStop.h"
#include <sys/dispatch.h>

void dispatcherThread(int channelID_Dispatcher, int connectionID_FSM_ESTOP, int connectionID_FSM, int connectionID_HAL_ACTUATORS, int connectionID_Encoder, int connectionID_Logger){
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
            case PULSE_ESTOP_OK:
                MsgSendPulse(connectionID_FSM, -1, msg.code, msg.value.sival_int);
                break;
            case PULSE_CONNECTION_LOST:
                printf("WATCHDOG: Connection lost to Machine 1\n");
                MsgSendPulse(connectionID_FSM, -1, PULSE_HIGH_LOW_MACHINE2, E_STOP);
                break;

            case PULSE_LOW_HIGH_MACHINE2:
            case PULSE_HIGH_LOW_MACHINE2:
            case PULSE_HIGHT:
                if(msg.value.sival_int == E_STOP || msg.value.sival_int == BUTTON_RESET || msg.value.sival_int == LBB){ //send to A2
                    client(msg);
                }
                MsgSendPulse(connectionID_FSM, -1, msg.code, msg.value.sival_int);
                break;

            case PULSE_LOW_HIGH_MACHINE1:
            case PULSE_HIGH_LOW_MACHINE1:
                MsgSendPulse(connectionID_FSM, -1, msg.code, msg.value.sival_int);
                break;

            case PULSE_M2_STATUS:
                client(msg);
                break;

            case PULSE_SEND_WP_TO_M2:
                MsgSendPulse(connectionID_FSM, -1, msg.code, msg.value.sival_int);
                break;

            case PULSE_FROM_FSM_TO_HAL:
            case PULSE_FLASH_ON:
            case PULSE_FLASH_OFF:
                MsgSendPulse(connectionID_HAL_ACTUATORS, -1, msg.code, msg.value.sival_int);
                break;

            case PULSE_CALIBRATION_OPERATION:
                MsgSendPulse(connectionID_Encoder, -1, msg.code, msg.value.sival_int);
                MsgSendPulse(connectionID_FSM, -1, msg.code, msg.value.sival_int);
                break;
        }
        MsgSendPulse(connectionID_Logger, -1, msg.code, msg.value.sival_int);
    }
    printf("Dispatcher Thread Done!\n");
}


