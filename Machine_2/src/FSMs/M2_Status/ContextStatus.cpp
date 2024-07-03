#include "../../../header/FSMs/M2_Status/ContextStatus.h"
#include "../../../header/FSMs/M2_Status/StatusMachineFree.h"



ContextStatus::ContextStatus(int connectionID_Dispatcher, ContextData* d) {
    state = new StatusMachineFree();
    actions.connectionID_Dispatcher = connectionID_Dispatcher;
    state->setActions(&actions);
    state->setData(d);
}

ContextStatus::~ContextStatus() {
    delete state;
}

void ContextStatus::m1_estop_pressed() {
    state->m1_estop_pressed();
}

void ContextStatus::m2_estop_pressed() {
    state->m2_estop_pressed();
}

void ContextStatus::error() {
    state->error();
}

void ContextStatus::error_ok(){
    state->error_ok();
}

void ContextStatus::estop_ok(){
    state->estop_ok();
}

void ContextStatus::start_pressed(){
    state->start_pressed();
}

void ContextStatus::stop_pressed(){
    state->stop_pressed();
}

void ContextStatus::lbe_free(){
    state->lbe_free();
}
void ContextStatus::lbb_blocked(){
    state->lbb_blocked();
}
void ContextStatus::lbc_blocked(){
    state->lbc_blocked();
}


