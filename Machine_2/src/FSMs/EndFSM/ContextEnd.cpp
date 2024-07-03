
#include "../../../header/FSMs/EndFSM/wait_for_info.h"
#include "../../../header/FSMs/EndFSM/ContextEnd.h"
#include "../../../header/FSMs/EndFSM/EndActions.h"
ContextEnd::ContextEnd(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d) {
    data = d;
    state = new Wait_for_info_End();
    actions.connectionID_Dispatcher = connectionID_Dispatcher;
    actions.connectionID_FSM = connectionID_FSM;
    state->setActions(&actions);
    state->setData(d);
}

ContextEnd::~ContextEnd() {
    delete state;
}

void ContextEnd::m1_estop_pressed() {
    state->m1_estop_pressed();
}

void ContextEnd::m2_estop_pressed() {
    state->m2_estop_pressed();
}

void ContextEnd::error_ok() {
    state->error_ok();
}

void ContextEnd::error() {
    state->error();
}
void ContextEnd::estop_ok(){
    state->estop_ok();
}

void ContextEnd::m2_lbe_blocked() {
    state->m2_lbe_blocked();
}

void ContextEnd::m2_lbe_free() {
    state->m2_lbe_free();
}


