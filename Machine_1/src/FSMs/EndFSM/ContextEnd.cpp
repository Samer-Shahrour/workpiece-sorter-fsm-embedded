#include "../../../header/FSMs/EndFSM/ContextEnd.h"
#include "../../../header/FSMs/ContextData.h"
#include "../../../header/FSMs/EndFSM/endActions.h"
#include "../../../header/FSMs/EndFSM/endIdle.h"



ContextEnd::ContextEnd(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d) {
    data = d;
    actions.connectionID_Dispatcher = connectionID_Dispatcher;
    actions.connectionID_FSMs = connectionID_FSM;
    data->connectionID_FSM = connectionID_FSM;
    state = new EndIdle();
    state->setActions(&actions);
    state->setData(data);
}

ContextEnd::~ContextEnd() {
    delete state;
}

void ContextEnd::m1_lbe_blocked(){
    state->m1_lbe_blocked();
}
void ContextEnd::m1_lbe_free(){
    state->m1_lbe_free();
}
void ContextEnd::error(){
    state->error();
}
void ContextEnd::error_ok(){
    state->error_ok();
}
void ContextEnd::estop_ok(){
    state->estop_ok();
}
void ContextEnd::m1_estop_pressed(){
    state->m1_estop_pressed();
}

void ContextEnd::m2_estop_pressed(){
    state->m2_estop_pressed();
}
void ContextEnd::m2_Ok(){
    state->m2_Ok();
}
void ContextEnd::m2_Nok(){
    state->m2_Nok();
}

void ContextEnd::m2_lbb_blocked(){
    state->m2_lbb_blocked();
}