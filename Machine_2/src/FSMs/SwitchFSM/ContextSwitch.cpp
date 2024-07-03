
#include "../../../header/FSMs/SwitchFSM/ContextSwitch.h"

#include "../../../header/FSMs/SwitchFSM/SwitchIdle.h"
ContextSwitch::ContextSwitch(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d) {
    data = d;
    state = new SwitchIdle();
    actions.connectionID_Dispatcher = connectionID_Dispatcher;
    actions.connectionID_FSM = connectionID_FSM;
    state->setActions(&actions);
    state->setData(d);
}

ContextSwitch::~ContextSwitch() {
    delete state;
}

void ContextSwitch::m1_estop_pressed() {
    state->m1_estop_pressed();
}

void ContextSwitch::m2_estop_pressed() {
    state->m2_estop_pressed();
}

void ContextSwitch::estop_ok(){
    state->estop_ok();
}

void ContextSwitch::error() {
    state->error();
}
void ContextSwitch::error_ok() {
    state->error_ok();
}
void ContextSwitch::lbc_blocked() {
    state->lbc_blocked();
}
void ContextSwitch::lbc_free() {
    state->lbc_free();
}
void ContextSwitch::lbs_blocked() {
    state->lbs_blocked();
}
void ContextSwitch::lbs_free() {
    state->lbs_free();
}
void ContextSwitch::metal_detected() {
    state->metal_detected();
}
