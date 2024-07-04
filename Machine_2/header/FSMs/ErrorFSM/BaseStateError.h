#pragma once
#include <iostream>
#include "ErrorActions.h"
#include "../ContextData.h"
using namespace std;

class BaseStateError {
protected:
    ErrorActions *actions;
    ContextData *data;
public:
    virtual ~BaseStateError(){};
    void setActions(ErrorActions *a){this->actions = a;};
    void setData(ContextData *d){this->data = d;};
    virtual void error(){};
    virtual void reset_pressed(){};
    virtual void estop_ok(){};
    virtual void m1_estop_pressed(){};
    virtual void m2_estop_pressed(){};
};
