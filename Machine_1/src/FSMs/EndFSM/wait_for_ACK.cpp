#include "../../../header/FSMs/EndFSM/endEstop.h"
#include "../../../header/FSMs/EndFSM/m2_free.h"
#include "../../../header/FSMs/EndFSM/endActions.h"
#include "../../../header/FSMs/EndFSM/wait_for_ACK.h"
#include "../../../header/FSMs/EndFSM/endIdle.h"
#include "../../../header/FSMs/EndFSM/m2_not_free.h"
#include "../../../header/FSMs/EndFSM/endError.h"

void Wait_for_ACK::m1_lbe_blocked() {
    new(this) M2_not_free;
}
void Wait_for_ACK::m2_lbb_blocked() { //ACK
    if(data->counter_End == data->queue.size()-1){
        actions->motor_stop();
    }
    new(this) EndIdle;
}

void Wait_for_ACK::m1_estop_pressed() {
    new(this) EndEstop;
}
void Wait_for_ACK::m2_estop_pressed(){
    new(this) EndEstop;
}

void Wait_for_ACK::error() {
    new(this) EndError;
}
