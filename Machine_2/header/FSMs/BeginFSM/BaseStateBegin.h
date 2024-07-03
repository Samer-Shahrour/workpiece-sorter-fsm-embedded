#pragma once
#include "BeginActions.h"
#include "../ContextData.h"
#include <iostream>

using namespace std;

class BaseStateBegin {
protected:
    BeginActions *actions;
    ContextData *data;
public:
    virtual ~BaseStateBegin(){};
    void setActions(BeginActions *a){this->actions = a;};
    void setData(ContextData *d){this->data = d;};

    virtual void m1_estop_pressed(){};
    virtual void m2_estop_pressed(){};
    virtual void estop_ok(){};
    virtual void info_received(){};
    virtual void m2_lbb_blocked(){};
    virtual void m2_lbb_free(){};
    virtual void m2_lbe_free(){};
    virtual void m2_lbc_blocked(){};
    virtual void time_out(){};
    virtual void error(){};
    virtual void error_ok(){};

};
