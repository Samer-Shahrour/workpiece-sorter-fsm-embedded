#include "../../../header/FSMs/BeginFSM/BeginActions.h"
#include "../../../header/FSMs/ContextData.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include <stdio.h>
#include <iostream>
#include "../../../header/myTimer.h"

void BeginActions::sendMsg(int msg) {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}

void BeginActions::motorStart() {
    sendMsg(MOVE_RIGHT);
}

void BeginActions::turnLEDQ1(bool on){
    if(on){
        sendMsg(LED_Q1 + LIGHT_ON);
    } else {
        sendMsg(LED_Q1 + LIGHT_OFF);
    }
}

void BeginActions::notifyFSMs() {
    MsgSendPulse(connectionID_FSMs, -1, PULSE_ERROR, 0);
}


void BeginActions::pushObject(ContextData* data) {
	Workpiece wp(connectionID_FSMs); //TODO zeiten ändern
	wp.startMinTimer(data->sectionAticks-500);
	wp.startMaxTimer(data->sectionAticks+500);
	data->queue.push_back(wp);
	for (unsigned i=0; i<	data->queue.size(); i++){
		printf("Workpiece[connectionID: %d,] \n", data->queue[i].getId());
	}
}

void BeginActions::turnGreen(bool on){
	if(on){
		sendMsg(GREEN + LIGHT_ON);
	} else {
		sendMsg(GREEN + LIGHT_OFF);
	}
}

void BeginActions::startTimerBegin(ContextData *data){
	myStartTimer(&data->timerStart_id, connectionID_FSMs, PULSE_TIME_OUT_BEGIN, 0, false, 500);
}
