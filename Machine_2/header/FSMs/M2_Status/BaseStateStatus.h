#pragma once

#include <iostream>
#include "../ContextData.h"
#include "StatusActions.h"

using namespace std;

class BaseStateStatus {

protected:
    ContextData *data;
    StatusActions *actions;
public:
    virtual ~BaseStateStatus(){};
    void setData(ContextData *d){this->data = d;};
    void setActions(StatusActions *a){this->actions = a;};


    virtual void start_pressed(){};
    virtual void stop_pressed(){};
    virtual void lbb_blocked(){};
    virtual void lbc_blocked(){};
    virtual void lbe_free(){};
    virtual void error(){};
    virtual void error_ok(){};
    virtual void estop_ok(){};
    virtual void m1_estop_pressed(){};
    virtual void m2_estop_pressed(){};
};
