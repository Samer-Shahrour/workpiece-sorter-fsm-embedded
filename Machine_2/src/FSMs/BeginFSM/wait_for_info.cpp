#include "../../../header/FSMs/BeginFSM/wait_for_info.h"
#include "../../../header/FSMs/BeginFSM/wait_for_wp.h"
#include "../../../header/FSMs/BeginFSM/BeginError.h"
#include "../../../header/FSMs/BeginFSM/BeginActions.h"
#include "../../../header/FSMs/BeginFSM/BeginEstop.h"

void Wait_for_info_Begin::info_received(){
    actions->pushObject(data);
    actions->startTransferTimer(data);
    actions->motorStart();
    new(this) Wait_for_wp;
}

void Wait_for_info_Begin::m2_lbb_blocked(){
    actions->notifyFSMs();
    new(this) BeginError;
}

void Wait_for_info_Begin::m2_estop_pressed() {
    new(this) BeginEstop;
}

void Wait_for_info_Begin::m1_estop_pressed() {
    new(this) BeginEstop;
}

void Wait_for_info_Begin::error() {
    new(this) BeginError;
}
