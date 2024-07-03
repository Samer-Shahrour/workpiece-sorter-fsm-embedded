#pragma once
#include "HMActions.h"
#include "BaseStateHM.h"
#include "../ContextData.h"



class ContextHM{
private:
    BaseStateHM *state;  // current state of state machine
    HMActions actions;
    ContextData *data;
public:
    ContextHM(int connectionID_FSM, int connectionID_Dispatcher, ContextData* d);
    virtual ~ContextHM();

    void error();
    void error_ok();
    void hight_changed(int hight);
    void m1_estop_pressed();
    void m2_estop_pressed();
    void estop_ok();
};
