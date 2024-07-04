#include "../../../header/FSMs/BeginFSM/BeginActions.h"
#include "../../../header/FSMs/ContextData.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include <stdio.h>
#include <iostream>
#include <chrono>
#include "../../../header/variables.h"
#include "../../../header/myTimer.h"

using namespace std;

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
	Workpiece wp(connectionID_FSMs);
    wp.minTimeStamp = createTimeStamp();
	wp.startMaxTimer(data->sectionAticks + EXTRA_TIME_FOR_SECTION_A);
	data->queue.push_back(wp);
}

void BeginActions::turnGreen(bool on){
	if(on){
		sendMsg(GREEN + LIGHT_ON);
	} else {
		sendMsg(GREEN + LIGHT_OFF);
	}
}

void BeginActions::startTimerBegin(ContextData *data){
	if(data->isSwitch){
		myStartTimer(&data->timerStart_id, connectionID_FSMs, PULSE_TIME_OUT_BEGIN, 0, false, MIN_DISTANC_SWITCH);
	}else {
		myStartTimer(&data->timerStart_id, connectionID_FSMs, PULSE_TIME_OUT_BEGIN, 0, false, MIN_DISTANC_EJECTOR);
	}
}

