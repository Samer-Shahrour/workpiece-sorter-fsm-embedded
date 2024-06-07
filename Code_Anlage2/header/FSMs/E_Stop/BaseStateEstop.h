#pragma once

#include "../../../header/FSMs/E_Stop/ContextDataEstop.h"
#include "../../../header/FSMs/E_Stop/EStopActions.h"
#include <iostream>
using namespace std;

class BaseStateEstop {
protected:
	EStopActions *actions;
public:
    virtual ~BaseStateEstop(){};
    void setActions(EStopActions *a){this->actions = a;};

    virtual void m1_reset_pressed(){};
    virtual void m1_estop_pressed() {};
    virtual void m1_estop_released(){};

    virtual void m2_reset_pressed(){};
    virtual void m2_estop_pressed(){};
    virtual void m2_estop_released(){};
    virtual void time_out_error_red_light(){};

};
