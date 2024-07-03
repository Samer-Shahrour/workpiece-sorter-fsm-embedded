#pragma once
#include "BaseStateBegin.h"
#include "BeginActions.h"
#include "../../../header/FSMs/ContextData.h"


class ContextBegin{
private:
    BaseStateBegin *state;  // current state of state machine
    BeginActions actions;
    ContextData *data;
public:
    ContextBegin(int connectionID_FSM, int connectionID_Dispatcher, ContextData *d);
    virtual ~ContextBegin();
    void m1_lbb_blocked();
    void m1_lbb_free();
    void time_out_begin();
    void externer_error();
    void error_ok();
    void estop_ok();
    void m1_estop_pressed();
    void m2_estop_pressed();
};
