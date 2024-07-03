#pragma once
#include "BeginActions.h"
#include "BaseStateBegin.h"
#include "../ContextData.h"



class ContextBegin{
private:
    BaseStateBegin *state;  // current state of state machine
    BeginActions actions;
    ContextData *data;
public:
    ContextBegin(int connectionID_FSM, int connectionID_Dispatcher, ContextData* d);
    virtual ~ContextBegin();
    void m1_estop_pressed();
    void m2_estop_pressed();
    void estop_ok();
    void info_received();
    void m2_lbb_blocked();
    void m2_lbb_free();
    void m2_lbe_free();
    void m2_lbc_blocked();
    void time_out();
    void error();
    void error_ok();
};
