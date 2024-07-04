#include "../../../header/FSMs/EndFSM/endEstop.h"
#include "../../../header/FSMs/EndFSM/m2_free.h"
#include "../../../header/FSMs/EndFSM/endActions.h"
#include "../../../header/FSMs/EndFSM/wait_for_ACK.h"
#include "../../../header/FSMs/EndFSM/m2_not_free.h"
#include "../../../header/FSMs/EndFSM/endError.h"
#include "../../../header/myTimer.h"

void M2_not_free::m2_Ok() {

    actions->motor_unblock();
    actions->restartAllTimer(data);
    actions->sendMsgTOM2(data, data->counter_End);
    new(this) M2_free;
}

void M2_not_free::m2_lbb_blocked() {
    actions->motor_block();
}

void M2_not_free::m1_lbe_free() {
    actions->notifyFSMs();
    new(this) EndError;
}

void M2_not_free::error() {
    new(this) EndError;
}

void M2_not_free::m1_estop_pressed() {
    new(this) EndEstop;
}

void M2_not_free::m2_estop_pressed() {
    new(this) EndEstop;
}