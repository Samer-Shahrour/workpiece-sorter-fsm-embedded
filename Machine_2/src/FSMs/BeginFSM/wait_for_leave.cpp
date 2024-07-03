#include "../../../header/FSMs/BeginFSM/wait_for_info.h"
#include "../../../header/FSMs/BeginFSM/wait_for_leave.h"
#include "../../../header/FSMs/BeginFSM/BeginError.h"
#include "../../../header/FSMs/BeginFSM/BeginActions.h"
#include "../../../header/FSMs/BeginFSM/BeginEstop.h"

void Wait_for_leave::m2_lbe_free(){
    new(this) Wait_for_info_Begin;
}
void Wait_for_leave::m2_lbc_blocked(){
    new(this) Wait_for_info_Begin;
}
void Wait_for_leave::m2_lbb_blocked(){
    actions->notifyFSMs();
    new(this) BeginError;
}

void Wait_for_leave::m2_estop_pressed() {
    new(this) BeginEstop;
}
void Wait_for_leave::m1_estop_pressed() {
    new(this) BeginEstop;
}
void Wait_for_leave::error() {
    new(this) BeginError;
}
