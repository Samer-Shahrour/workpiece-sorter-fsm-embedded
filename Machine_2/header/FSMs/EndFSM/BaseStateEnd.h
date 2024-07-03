#pragma once
#include <iostream>
#include "EndActions.h"
#include "../ContextData.h"

using namespace std;

class BaseStateEnd {
protected:
    EndActions *actions;
    ContextData *data;
public:
    virtual ~BaseStateEnd(){};
    void setActions(EndActions *a){this->actions = a;};
    void setData(ContextData *d){this->data = d;};

    virtual void error(){};
    virtual void error_ok(){};
    virtual void m2_lbe_blocked(){};
    virtual void m2_lbe_free(){};
    virtual void estop_ok(){};

    virtual void m1_estop_pressed(){};
    virtual void m2_estop_pressed(){};
};
