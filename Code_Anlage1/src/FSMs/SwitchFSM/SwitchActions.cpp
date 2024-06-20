#include <sys/neutrino.h>
#include "../../../header/FSMs/SwitchFSM/SwitchActions.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/PulseCodes.h"
#include <iostream>

void SwitchActions::sendMsg(int msg){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}
void SwitchActions::notifyFSms(void){
    MsgSendPulse(connectionID_FSM, -1, PULSE_ERROR, 0);
}

void SwitchActions::letThrough(void){
    sendMsg(LET_THROUGH);
}

void SwitchActions::sortOut(void){
    sendMsg(SORT_OUT);
}

void SwitchActions::turnYellow(bool on){
    if(on){
        sendMsg(YELLOW + LIGHT_ON);
    } else {
        sendMsg(YELLOW + LIGHT_OFF);
    }
}

void SwitchActions::deleteMaxTimer(ContextData* data, int id){
    data->queue[id].deleteMaxTimer();
}


void SwitchActions::deleteFromVector(ContextData* data, int id){
    data->counter_HM--;
    data->counter_switch--;
    data->queue.erase(data->queue.begin() + id);
    printf("deleted ID: %d\n", id);
}


