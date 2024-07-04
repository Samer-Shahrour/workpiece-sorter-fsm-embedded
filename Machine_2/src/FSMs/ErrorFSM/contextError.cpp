
#include "../../../header/FSMs/ErrorFSM/contextError.h"
#include "../../../header/FSMs/ErrorFSM/IdleError.h"

ContextError::ContextError(int connectionID_FSM, int connectionID_Dispatcher, ContextData* d) {
	data = d;
	state = new IdleError();
	actions.connectionID_Dispatcher = connectionID_Dispatcher;
    actions.connectionID_FSM = connectionID_FSM;
    state->setActions(&actions);
    state->setData(data);
}

ContextError::~ContextError() {
    delete state;
}

void ContextError::m1_estop_pressed() {
    state->m1_estop_pressed();
}

void ContextError::m2_estop_pressed() {
    state->m2_estop_pressed();
}

void ContextError::reset_pressed() {
    state->reset_pressed();
}

void ContextError::error() {
    state->error();
}
void ContextError::estop_ok(){
    state->estop_ok();
}

