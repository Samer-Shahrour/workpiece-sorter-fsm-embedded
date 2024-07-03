#pragma once
#include "BaseStateEnd.h"
#include "endActions.h"
#include "../../../header/FSMs/ContextData.h"


class ContextEnd{
private:
    BaseStateEnd *state;  // current state of state machine
    EndActions actions;
    ContextData *data;
public:
    ContextEnd(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d);
    virtual ~ContextEnd();
    void m1_lbe_blocked();
    void m1_lbe_free();
    void error();
    void error_ok();
    void estop_ok();
    void m1_estop_pressed();
    void m2_estop_pressed();
    void m2_Ok();
    void m2_Nok();
    void m2_lbb_blocked();
};
