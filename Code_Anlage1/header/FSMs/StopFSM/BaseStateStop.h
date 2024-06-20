#pragma once
#include <iostream>

#include "StopActions.h"
#include "../ContextData.h"
using namespace std;

class BaseStateStop {
protected:
    StopActions *actions;
    ContextData *data;
public:
    virtual ~BaseStateStop(){};
    void setActions(StopActions *a){this->actions = a;};
    void setData(ContextData *d){this->data = d;};

    virtual void start_pressed(){};
    virtual void stop_pressed(){};

    virtual void error(){};
    virtual void error_ok(){};

    virtual void estop_ok(){};
    virtual void m1_estop_pressed(){};
    virtual void m2_estop_pressed(){};
};
