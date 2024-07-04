#include <sys/neutrino.h>
#include "../../../header/FSMs/BeginFSM/BeginActions.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/myTimer.h"

#define SECTION_E_TIME          2*1000
#define SECTION_A_EXTRATIME     1000

void BeginActions::sendMsg(int msg){
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_FROM_FSM_TO_HAL, msg);
}

void BeginActions::notifyFSMs() {
    MsgSendPulse(connectionID_FSM, -1, PULSE_ERROR, 0);
}

void BeginActions::motorStart() {
    sendMsg(MOVE_RIGHT);
}

void BeginActions::startWPTimer(ContextData* data) {
    data->queue[0].startMaxTimer(data->sectionAticks+SECTION_A_EXTRATIME);
}

void BeginActions::startTransferTimer(ContextData *data) {
    myStartTimer(&data->transfer_timer_id, connectionID_FSM, PULSE_TIME_OUT_WP_MAX, 0, false, SECTION_E_TIME);
}

void BeginActions::deleteTransferTimer(ContextData *data) {
    myDeleteTimer(data->transfer_timer_id);
}
void BeginActions::pushObject(ContextData *data) {
    Workpiece wp(data->connectionID_FSM);
    wp.minTimeStamp = createTimeStamp();
    data->queue.push_back(wp);
}
