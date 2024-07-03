#include "../../../header/FSMs/EndFSM/endEstop.h"
#include "../../../header/FSMs/EndFSM/m2_free.h"
#include "../../../header/FSMs/EndFSM/endActions.h"
#include "../../../header/FSMs/EndFSM/wait_for_ACK.h"
#include "../../../header/FSMs/EndFSM/m2_not_free.h"
#include "../../../header/FSMs/EndFSM/endError.h"
#include "../../../header/myTimer.h"

#define TOLERANZ 500

void M2_free::m1_lbe_free() {
    //data->queue[data->counter_End].startMaxTimer(data->sectionCticks + TOLERANZ);
    //data->counter_End++;
    new(this) Wait_for_ACK;
}

void M2_free::m2_Nok() {
    actions->motor_block();
    new(this) M2_not_free;
}

void M2_free::error() {
    new(this) EndError;
}

void M2_free::m1_estop_pressed() {
    new(this) EndEstop;
}

void M2_free::m2_estop_pressed() {
    new(this) EndEstop;
}