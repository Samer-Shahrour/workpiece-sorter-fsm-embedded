#pragma once
#include "../../../header/FSMs/ErrorFSM/BaseStateError.h"
#include "../../../header/FSMs/ErrorFSM/ErrorActions.h"



class ContextError{
private:
    BaseStateError *state;  // current state of state machine
    ErrorActions actions;
    ContextData *data;

public:
    ContextError(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d);
    virtual ~ContextError();
    void error();
	void reset_pressed();
	void estop_ok();
	void m1_estop_pressed();
	void m2_estop_pressed();
};
