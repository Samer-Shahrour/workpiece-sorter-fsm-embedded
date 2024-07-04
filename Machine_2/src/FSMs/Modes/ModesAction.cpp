#include <sys/neutrino.h>
#include "../../../header/FSMs/Modes/ModesActions.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/Hal/Sensors.h"
#include "../../../header/ChannelUtils.h"
#include "../../../header/myTimer.h"
#include "../../../header/FSMs/ContextData.h"
#include "../../../header/variables.h"
void ModesActions::sendMsg(int msg){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}

void ModesActions::startButtonTimer(ContextData *data){
    myStartTimer(&data->timerStart_id, data->connectionID_FSM, PULSE_TIME_START, 0, false, 1000);
}

void ModesActions::startTickTimer(ContextData *data){
    myStartTimer(&data->timer_FB, data->connectionID_FSM, PULSE_TICK_CALIBRATION, 0, true, 10);
}

void ModesActions::turnGreen(bool on){
    if(on){
        sendMsg(GREEN + LIGHT_ON);
    } else {
        sendMsg(GREEN + LIGHT_OFF);
    }
}

void ModesActions::turnLEDQ1(bool on){

	   if(on){
	        sendMsg(LED_Q1 + LIGHT_ON);
	    } else {
	        sendMsg(LED_Q2+ LIGHT_OFF);
	    }
}
void ModesActions::startGreenFLASH(){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FLASH_ON, GREEN);
}

void ModesActions::stopGreenFLASH(){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FLASH_OFF, GREEN);
}


void ModesActions::deleteTimer(ContextData *data) {
    myDeleteTimer(data->timer_FB);
}

void ModesActions::motor_start(bool start) {
    if(start){
        sendMsg(MOVE_RIGHT);
    } else{
        sendMsg(STOP);
    }
}

void ModesActions::motor_fast(bool fast) {
    if(fast){
        sendMsg(MOTOR_FAST);
    } else{
        sendMsg(MOTOR_SLOW);
    }
}

void ModesActions::let_through(bool let_through) {
    if(let_through){
        sendMsg(LET_THROUGH);
    } else {
        sendMsg(SORT_OUT);
    }
}

void ModesActions::setCalibrationMode(bool calibration){
    if(calibration){
        MsgSendPulse(connectionID_Dispatcher, -1, PULSE_CALIBRATION_OPERATION, 1);
        //MsgSendPulse(connectionID_FSMs, -1, PULSE_CALIBRATION_OPERATION, 1);
    } else { // Operation
        MsgSendPulse(connectionID_Dispatcher, -1, PULSE_CALIBRATION_OPERATION, 0);
        //MsgSendPulse(connectionID_FSMs, -1, PULSE_CALIBRATION_OPERATION, 0);
    }
}

void ModesActions::incrementSection(uint64_t *section) {
    *section += 10;
}
void ModesActions::sendM2_OK() {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_M2_STATUS, M2_OK);
}
