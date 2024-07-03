#pragma once
#include "EndActions.h"
#include "BaseStateEnd.h"
#include "EndActions.h"
#include "../ContextData.h"



class ContextEnd{
private:
    BaseStateEnd *state;  // current state of state machine
    EndActions actions;
    ContextData *data;
public:
    ContextEnd(int connectionID_FSM, int connectionID_Dispatcher, ContextData* d);
    virtual ~ContextEnd();

    void error_ok();
    void error();
    void m2_lbe_blocked();
    void m2_lbe_free();
    void estop_ok();
    void m1_estop_pressed();
    void m2_estop_pressed();
};
