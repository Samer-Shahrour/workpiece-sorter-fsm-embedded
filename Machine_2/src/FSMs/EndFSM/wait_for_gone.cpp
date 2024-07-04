#include "../../../header/FSMs/EndFSM/wait_for_info.h"
#include "../../../header/FSMs/EndFSM/wait_for_gone.h"
#include "../../../header/FSMs/EndFSM/endError.h"
#include "../../../header/FSMs/EndFSM/EndActions.h"
#include "../../../header/FSMs/EndFSM/endEstop.h"



void Wait_for_gone::m2_lbe_free(){
    //actions->sendM2_OK();
    actions->motorUnblock();
    data->queue.clear();
    actions->motorStop();
    new(this) Wait_for_info_End;
}

void  Wait_for_gone::m2_estop_pressed() {
    new(this) EndEstop;
}

void  Wait_for_gone::m1_estop_pressed() {
    new(this) EndEstop;
}

void  Wait_for_gone::error() {
    new(this) EndError;
}
