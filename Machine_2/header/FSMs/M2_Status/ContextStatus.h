#pragma once
#include "BaseStateStatus.h"
#include "StatusActions.h"

class ContextStatus{
private:
    BaseStateStatus *state;  // current state of state machine
    ContextData *data;
    StatusActions actions;
public:
    ContextStatus(int connectionID_Dispatcher, ContextData *d);
    virtual ~ContextStatus();

    void error();
    void error_ok();
    void lbb_blocked();
    void lbc_blocked();
    void lbe_free();
    void stop_pressed();
    void start_pressed();
    void estop_ok();
    void m1_estop_pressed();
    void m2_estop_pressed();
};
