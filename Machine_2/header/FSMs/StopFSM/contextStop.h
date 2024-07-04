#pragma once
#include "StopActions.h"
#include "BaseStateStop.h"
#include "../ContextData.h"

class ContextStop{
private:
    BaseStateStop *state;  // current state of state machine
    StopActions actions;
    ContextData *data;

public:
    ContextStop(int connectionID_FSM, int connectionID_Dispatcher, ContextData* d);
    virtual ~ContextStop();
    void start_pressed();
	void stop_pressed();
	void error();
	void error_ok();
	void estop_ok();
	void m1_estop_pressed();
	void m2_estop_pressed();
	void m2_lbe_free();
	void m2_lbe_blocked();
};
