#include "../../../header/FSMs/EndFSM/endActions.h"
#include "../../../header/FSMs/ContextData.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include <stdio.h>
#include <iostream>
#include <chrono>

#include "../../../header/variables.h"
#include "../../../header/myTimer.h"

#define EXTRA_TIME		200

using namespace std;

void EndActions::sendMsg(int msg) {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}

void EndActions::motor_block() {
    sendMsg(BLOCK);
}

void EndActions::motor_stop() {
    sendMsg(STOP);
}

void EndActions::motor_unblock(){
    sendMsg(UNBLOCK);
}

void EndActions::notifyFSMs() {
    MsgSendPulse(connectionID_FSMs, -1, PULSE_ERROR, 0);
}
void EndActions::sendMsgTOM2(ContextData *data, int id){
    int wpTyp = 0;
    if (data->queue[id].getType() == WorkpieceType::FlatWorkpiece){ //send to A2
        wpTyp = WP_FLAT;
    }
    else if (data->queue[id].getType() == WorkpieceType::MetalWorkpiece){
        wpTyp = WP_METAL;
    }
    else{
        wpTyp = WP_UNDEFIND;
    }
   MsgSendPulse(connectionID_Dispatcher, -1, PULSE_SEND_WP_TO_M2,  wpTyp);
}
void EndActions::deleteAllTimer(ContextData* data){
    myDeleteTimer(data->timerStart_id);
    for (int i = 0; i < data->queue.size(); i++){
        data->queue[i].deleteMaxTimer();
    }
}

void EndActions::getRemainingTime(ContextData* data){
    data->timerStart_reminingTime = getRemainingTimeInMS(data->timerStart_id); //get timer FB
    for (int i = 0; i < data->queue.size(); i++){
        if(data->queue[i].still_on_belt) {
            data->queue[i].getRemainingMaxTime();
        }
    }
}

void EndActions::restartAllTimer(ContextData* data){
    if(data->timerStart_reminingTime){
        myStartTimer(&data->timerStart_id, connectionID_Dispatcher, PULSE_TIME_OUT_BEGIN, 0, false, data->timerStart_reminingTime);
    }
    for (int i = 0; i < data->queue.size(); ++i) {
        if(data->queue[i].still_on_belt){
            data->queue[i].restartMaxTimer(EXTRA_TIME);
        }
    }
}
