#pragma once

#include <iostream>
#include "SwitchActions.h"
#include "../ContextData.h"

using namespace std;

class BaseStateSwitch {
protected:
    SwitchActions *actions;
    ContextData *data;
public:
    virtual ~BaseStateSwitch(){};
    void setActions(SwitchActions *a){this->actions = a;};
    void setData(ContextData *d){this->data = d;};

    virtual void lbs_blocked(){};
    virtual void metal_detected(){};
    virtual void lbs_free(){};
    virtual void lbc_blocked(){};
    virtual void lbc_free(){};

    virtual void error(){};
    virtual void error_ok(){};
    virtual void estop_ok(){};
    virtual void m1_estop_pressed(){};
    virtual void m2_estop_pressed(){};

};
