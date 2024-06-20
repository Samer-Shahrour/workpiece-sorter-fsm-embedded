#include "../../../header/FSMs/ErrorFSM/ErrorActions.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"


void ErrorActions::sendMsg(int msg) {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}

void ErrorActions::motorStop() {
    sendMsg(STOP);
}

void ErrorActions::motorBlock() {
    sendMsg(BLOCK);
}

void ErrorActions::motorUnblock() {
    sendMsg(UNBLOCK);
}

void ErrorActions::startRedFLASH() {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FLASH_ON, RED);
}

void ErrorActions::stopRedFLASH() {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FLASH_OFF, RED);
}

void ErrorActions::turnAllOff() {
    sendMsg(GREEN + LIGHT_OFF);
    sendMsg(RED + LIGHT_OFF);
    sendMsg(YELLOW + LIGHT_OFF);
}

void ErrorActions::deleteAllTimer(ContextData *data){
	for (int i = 0; i < data->queue.size(); i++){
		data->queue[i].deleteMinTimer();
		data->queue[i].deleteMaxTimer();
	}
}

void ErrorActions::sendErrorOK() {
    MsgSendPulse(connectionID_FSM, -1, PULSE_ERROR_OK, 0);
}

void ErrorActions::turnGreen(bool on){
    if(on){
        sendMsg(GREEN + LIGHT_ON);
    } else {
        sendMsg(GREEN + LIGHT_OFF);
    }
}
