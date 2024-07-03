#pragma once
#include "SwitchActions.h"
#include "BaseStateSwitch.h"
#include "../ContextData.h"

class ContextSwitch{
private:
    BaseStateSwitch *state;  // current state of state machine
    SwitchActions actions;
    ContextData *data;

public:
    ContextSwitch(int connectionID_FSM, int connectionID_Dispatcher, ContextData* d);
    virtual ~ContextSwitch();
    void lbs_blocked();
    void lbs_free();
    void lbc_blocked();
    void lbc_free();
    void metal_detected();

    void error();
    void error_ok();
    void estop_ok();
    void m1_estop_pressed();
    void m2_estop_pressed();
};
