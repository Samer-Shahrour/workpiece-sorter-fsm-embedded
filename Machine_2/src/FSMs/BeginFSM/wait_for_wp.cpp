#include "../../../header/FSMs/BeginFSM/wait_for_leave.h"
#include "../../../header/FSMs/BeginFSM/BeginError.h"
#include "../../../header/FSMs/BeginFSM/BeginActions.h"
#include "../../../header/FSMs/BeginFSM/BeginEstop.h"
#include "../../../header/FSMs/BeginFSM/wait_for_wp.h"

void Wait_for_wp::m2_lbb_free(){
    actions->deleteTransferTimer(data);
    actions->startWPTimer(data);
    new(this) Wait_for_leave;
}

void Wait_for_wp::m2_estop_pressed() {
    new(this) BeginEstop;
}
void Wait_for_wp::m1_estop_pressed() {
    new(this) BeginEstop;
}
void Wait_for_wp::error() {
    new(this) BeginError;
}
