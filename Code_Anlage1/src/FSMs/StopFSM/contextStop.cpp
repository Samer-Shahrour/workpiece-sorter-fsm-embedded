
#include "../../../header/FSMs/StopFSM/contextStop.h"
#include "../../../header/FSMs/StopFSM/IdleStop.h"

ContextStop::ContextStop(int connectionID_FSM, int connectionID_Dispatcher, ContextData* d) {
	state = new IdleStop();
	actions.connectionID_Dispatcher = connectionID_Dispatcher;
    actions.connectionID_FSM = connectionID_FSM;
    state->setActions(&actions);
    state->setData(d);
}

ContextStop::~ContextStop() {
    delete state;
}

void ContextStop::m1_estop_pressed() {
    state->m1_estop_pressed();
}

void ContextStop::m2_estop_pressed() {
    state->m2_estop_pressed();
}

void ContextStop::error() {
    state->error();
}

void ContextStop::error_ok(){
	state->error_ok();
}

void ContextStop::estop_ok(){
    state->estop_ok();
}

void ContextStop::start_pressed(){
	state->start_pressed();
}

void ContextStop::stop_pressed(){
	state->stop_pressed();
}

