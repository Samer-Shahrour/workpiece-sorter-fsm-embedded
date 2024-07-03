#pragma once
#include <iostream>
#include "endActions.h"
#include "../../../header/FSMs/ContextData.h"
using namespace std;

class BaseStateEnd {
protected:
    ContextData *data;
    EndActions *actions;
public:
    virtual ~BaseStateEnd(){};
    void setActions(EndActions *a){this->actions = a;};
    void setData(ContextData *d){this->data = d;};

    virtual void m1_lbe_blocked(){};
    virtual void m1_lbe_free(){};
    virtual void m2_lbb_blocked(){};
    virtual void error(){};
    virtual void error_ok(){};
    virtual void estop_ok(){};
    virtual void m1_estop_pressed(){};
    virtual void m2_estop_pressed(){};
    virtual void m2_Ok(){};
    virtual void m2_Nok(){};
};
