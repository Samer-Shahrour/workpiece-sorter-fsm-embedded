#include <sys/neutrino.h>
#include "../../../header/FSMs/E_Stop/EStopActions.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/Logik/Workpiece.h"

int connectionID_Dispatcher;
void EStopActions::sendMsg(int msg){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}

void EStopActions::sendEstopOK(){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_ESTOP_OK, 0);
}

void EStopActions::turnRed(bool on){
    if(on){
        sendMsg(RED + LIGHT_ON);
    } else {
        sendMsg(RED + LIGHT_OFF);
    }
}

void EStopActions::turnLEDQ2(bool on){
    if(on){
        sendMsg(LED_Q2 + LIGHT_ON);
    } else {
        sendMsg(LED_Q2 + LIGHT_OFF);
    }
}

void EStopActions::startRedFLASH(){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FLASH_ON, RED);
}

void EStopActions::stopRedFLASH(){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FLASH_OFF, RED);
}

void EStopActions::motorUnblock(void){
    sendMsg(UNBLOCK);
}

void EStopActions::deleteAllTimer(ContextData *data){
	for (int i = 0; i < data->queue.size(); i++){
		data->queue[i].deleteMaxTimer();
	}
}

void EStopActions::resetAllData(ContextData *data){
    data->typCounter = 0;
    data->counter_switch = 0;
    data->counter_HM = 0;
    data->counter_End = 0;
    data->counter_Chute = 0;
    data->m2_free = false;
    data->queue.clear();
    data->timerStart_reminingTime = 0;
    resetGenerater();
}

void EStopActions::resetMachineActions(void){
    sendMsg(GREEN + LIGHT_OFF);
    sendMsg(YELLOW + LIGHT_OFF);
    sendMsg(LED_Q1 + LIGHT_OFF);
    sendMsg(BLOCK);
    sendMsg(STOP);
    sendMsg(MOTOR_FAST);
}
