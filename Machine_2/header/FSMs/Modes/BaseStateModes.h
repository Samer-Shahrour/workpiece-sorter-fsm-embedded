#pragma once
#include "../../../header/FSMs/Modes/ModesActions.h"
#include "../../../header/FSMs/ContextData.h"
#include <iostream>
using namespace std;

class BaseStateModes {
protected:
    ModesActions *actions;
    ContextData *data;
public:
    virtual ~BaseStateModes(){};
    void setActions(ModesActions *a){this->actions = a;};
    void setData(ContextData *d){this->data = d;};
    virtual void m1_start_pressed(){};
    virtual void m1_start_released(){};
    virtual void time_out_start(){};
    virtual void estop_ok(){};
    virtual void m1_estop_pressed(){};
    virtual void m2_estop_pressed(){};

    //for Calibration
    virtual void lbb_blocked(){};
    virtual void lbb_free(){};
    virtual void hight_changed(){};
    virtual void lbs_blocked(){};
    virtual void lbc_blocked(){};
    virtual void lbe_blocked(){};
    virtual void incrementSection(){};
};
