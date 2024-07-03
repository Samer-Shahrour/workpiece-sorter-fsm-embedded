#include "../../../header/FSMs/StopFSM/StopActions.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/FSMs/ContextData.h"
#include "../../../header/myTimer.h"
#include <iostream>

#define EXTRA_TIME 200

void StopActions::sendMsg(int msg) {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}

void StopActions::deleteAllTimer(ContextData* data) {
    myDeleteTimer(data->timerStart_id);
    for (int i = 0; i < data->queue.size(); i++){
        data->queue[i].deleteMaxTimer();
    }
}

void StopActions::getRemainingTime(ContextData* data) {
    data->timerStart_reminingTime = getRemainingTimeInMS(data->timerStart_id); //get timer FB
    for (int i = 0; i < data->queue.size(); i++){
        data->queue[i].getRemainingMaxTime();
    }
}

void StopActions::motorBlock() {
    sendMsg(BLOCK);
}

void StopActions::restartAllTimer(ContextData* data) {
    if(data->timerStart_reminingTime){
        myStartTimer(&data->timerStart_id, connectionID_Dispatcher, PULSE_TIME_OUT_BEGIN, 0, false, data->timerStart_reminingTime);
    }
    for (int i = 0; i < data->queue.size(); ++i) {
        data->queue[i].restartMaxTimer(EXTRA_TIME);
    }
}

void StopActions::motorUnblock() {
    sendMsg(UNBLOCK);
}
