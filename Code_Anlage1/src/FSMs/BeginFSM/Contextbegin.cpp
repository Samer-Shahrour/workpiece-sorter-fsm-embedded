#include "../../../header/FSMs/BeginFSM/ContextBegin.h"
#include "../../../header/FSMs/BeginFSM/wait_for_wp.h"
#include "../../../header/FSMs/ContextData.h"


ContextBegin::ContextBegin(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d) {
    data = d;
    actions.connectionID_Dispatcher = connectionID_Dispatcher;
    actions.connectionID_FSMs = connectionID_FSM;
    data->connectionID_FSM = connectionID_FSM;
    state = new Wait_for_wp();
    state->setActions(&actions);
    state->setData(data);
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

void ContextBegin::m1_lbb_blocked(){
    state->m1_lbb_blocked();
}

void ContextBegin::m1_lbb_free() {
    state->m1_lbb_free();
}

void ContextBegin::estop_ok(){
    state->estop_ok();
}
void ContextBegin::error_ok(){
    state->error_ok();
}
void ContextBegin::time_out_begin(){
    state->time_out_begin();
}
void ContextBegin::externer_error(){
    state->externer_error();
}

