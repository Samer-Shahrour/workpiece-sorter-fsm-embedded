#include "../../../header/FSMs/hightMeasurmentFSM/HMActions.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/variables.h"
#include "../../../header/myTimer.h"
#include <iostream>


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
            data->queue[i].restartMaxTimer(500);
        }
	}
}

void HMActions::getRemainingTime(ContextData *data, int id) {
	for (int i = 0; i < data->queue.size(); i++){
        if(i != id){
            data->queue[i].getRemainingMaxTime();
        }
	}
}

void HMActions::notifyFSMs() {
    MsgSendPulse(connectionID_FSM, -1, PULSE_ERROR, 0);
}

void HMActions::setWpType(ContextData *data, int type) {
   if(type == WP_FLAT){
       data->queue[0].setType(WorkpieceType::FlatWorkpiece);
   } else if(type == WP_UNDEFIND){
       data->queue[0].setType( WorkpieceType::DefectiveWorkpiece);
   }
}

void HMActions::incrementSwitchTime() {
    sendMsg(HM_SLOW);
}


bool HMActions::checkWpType(ContextData* data){
    if(data->queue[0].getType() == WorkpieceType::DefectiveWorkpiece){
        printf("typ from M2 = defective\n");
    } else if(data->queue[0].getType() == WorkpieceType::MetalWorkpiece){
        printf("typ from M2 = MetalWorkpiece\n");
    } else if(data->queue[0].getType() == WorkpieceType::FlatWorkpiece){
        printf("typ from M2 = FlatWorkpiece\n");
    }

    if(data->queue[0].type_received_from_m1 == WorkpieceType::DefectiveWorkpiece){
        printf("typ from M1 = defective\n");
    } else if(data->queue[0].type_received_from_m1 == WorkpieceType::MetalWorkpiece){
        printf("typ from M1 = MetalWorkpiece\n");
    } else if(data->queue[0].type_received_from_m1 == WorkpieceType::FlatWorkpiece){
        printf("typ from M1 = FlatWorkpiece\n");
    }

    if(data->queue[0].getType() == WorkpieceType::DefectiveWorkpiece && (data->queue[0].type_received_from_m1 == WorkpieceType::MetalWorkpiece)){ //-> wird beim metal sensor erkannt, falls das kein metal ist
        return true;
    }
    if(data->queue[0].type_received_from_m1 == data->queue[0].getType()) {
        return true;
    } else {
        return false;
    }
}
