#include "../../../header/FSMs/hightMeasurmentFSM/HMActions.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/variables.h"
#include "../../../header/myTimer.h"

#define EXTRA_TIME 1000

void HMActions::sendMsg(int msg) {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}

void HMActions::motor_fast(bool on) {
    if(on){
        sendMsg(MOTOR_FAST);
    } else {
        sendMsg(MOTOR_SLOW);
    }
}

void HMActions::deleteMaxTimer(ContextData *data, int id) {
    data->queue[id].deleteMaxTimer();
}

void HMActions::deleteAllTimer(ContextData *data) {
	for (int i = 0; i < data->queue.size(); i++){
		data->queue[i].deleteMaxTimer();
	}
}

void HMActions::restartMaxTimer(ContextData *data, int id){
	for (int i = 0; i < data->queue.size(); ++i) {
        if(i != id && data->queue[id].still_on_belt){
            data->queue[i].restartMaxTimer(EXTRA_TIME);
        }
	}
}

void HMActions::getRemainingTime(ContextData *data, int id) {
	for (int i = 0; i < data->queue.size(); i++){
        if(i != id){
            //data->queue[i].getRemainingMinTime(); // TODO: benutzen wir nicht denke ich -> auskommentiert
            data->queue[i].getRemainingMaxTime();
        }
	}
}

void HMActions::notifyFSMs() {
    MsgSendPulse(connectionID_FSM, -1, PULSE_ERROR, 0);
}

void HMActions::setWpType(ContextData *data, int id, int type) {
   if(type == WP_FLAT){
       data->queue[id].setType(WorkpieceType::FlatWorkpiece);
   } else if(type == WP_UNDEFIND){
       data->queue[id].setType( WorkpieceType::DefectiveWorkpiece);
   }
}

void HMActions::incrementSwitchTime() {
    sendMsg(HM_SLOW);
}
