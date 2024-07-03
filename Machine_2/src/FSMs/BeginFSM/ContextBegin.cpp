
#include "../../../header/FSMs/BeginFSM/BeginError.h"
#include "../../../header/FSMs/BeginFSM/ContextBegin.h"
#include "../../../header/FSMs/BeginFSM/wait_for_info.h"
ContextBegin::ContextBegin(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d) {
    data = d;
    state = new Wait_for_info_Begin();
    actions.connectionID_Dispatcher = connectionID_Dispatcher;
    actions.connectionID_FSM = connectionID_FSM;
    state->setActions(&actions);
    state->setData(d);
}

ContextBegin::~ContextBegin() {
    delete state;
}

void ContextBegin::m1_estop_pressed() {
    state->m1_estop_pressed();
}

void ContextBegin::m2_estop_pressed() {
    state->m2_estop_pressed();
}

void ContextBegin::error_ok() {
    state->error_ok();
}

void ContextBegin::error() {
    state->error();
}
void ContextBegin::estop_ok(){
    state->estop_ok();
}

void ContextBegin::info_received() {
    state->info_received();
}

void ContextBegin::m2_lbb_blocked() {
    state->m2_lbb_blocked();
}

void ContextBegin::m2_lbb_free(){
    state->m2_lbb_free();
}
void ContextBegin::m2_lbc_blocked(){
    state->m2_lbc_blocked();
}
void ContextBegin::m2_lbe_free() {
    state->m2_lbe_free();
}
void ContextBegin::time_out() {
    state->time_out();
}

