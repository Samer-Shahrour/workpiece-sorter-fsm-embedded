#include <sys/neutrino.h>
#include "../../../header/FSMs/EndFSM/EndActions.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/variables.h"
#include "../../../header/myTimer.h"

void EndActions::sendMsg(int msg){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}

void EndActions::notifyFSMs() {
    MsgSendPulse(connectionID_FSM, -1, PULSE_ERROR, 0);
}

void EndActions::motorBlock() {
    sendMsg(BLOCK);
}

void EndActions::motorUnblock() {
    sendMsg(UNBLOCK);
}

void EndActions::sendM2_OK() {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_M2_STATUS, M2_OK);
}

void EndActions::deleteMaxTimer(ContextData* data) {
    data->queue[0].deleteMaxTimer();
}
void EndActions::motorStop() {
    sendMsg(STOP);
}