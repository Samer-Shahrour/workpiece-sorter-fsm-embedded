#include "../../../header/FSMs/Modes/BaseStateModes.h"
#include "../../../header/FSMs/Modes/IdleModes.h"
#include "../../../header/FSMs/Modes/contextModes.h"

ContextModes::ContextModes(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d){
    data = d;
    actions.connectionID_Dispatcher = connectionID_Dispatcher;
    data->connectionID_FSM = connectionID_FSM;
    state = new IdleModes();
    state->setActions(&actions);
    state->setData(data);
}

ContextModes::~ContextModes(){
    delete state;
}

void ContextModes::m1_start_pressed(){
    state->m1_start_pressed();
}

void ContextModes::m1_start_released(){
    state->m1_start_released();
}

void ContextModes::time_out_start(){
    state->time_out_start();
}

void ContextModes::m1_estop_pressed() {
    state->m1_estop_pressed();
}

void ContextModes::m2_estop_pressed() {
    state->m2_estop_pressed();
}

void ContextModes::estop_ok() {
    state->estop_ok();
}

//for Calibration
void ContextModes::lbb_blocked(){
    state->lbb_blocked();
}

void ContextModes::lbb_free(){
    state->lbb_free();
}

void ContextModes::hight_changed(){
    state->hight_changed();
}

void ContextModes::lbs_blocked(){
    state->lbs_blocked();
}

void ContextModes::lbc_blocked(){
    state->lbc_blocked();
}

void ContextModes::lbe_blocked(){
    state->lbe_blocked();
}

void ContextModes::incrementSection(){
    state->incrementSection();
}
