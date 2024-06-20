#pragma once
#include <iostream>
#include "BeginActions.h"
#include "../../../header/FSMs/ContextData.h"
using namespace std;

class BaseStateBegin {
protected:
    ContextData *data;
    BeginActions *actions;
public:
    virtual ~BaseStateBegin(){};
    void setActions(BeginActions *a){this->actions = a;};
    void setData(ContextData *d){this->data = d;};

    virtual void m1_lbb_blocked(){};
    virtual void m1_lbb_free(){};
    virtual void time_out_begin(){};
    virtual void externer_error(){};
    virtual void error_ok(){};
    virtual void estop_ok(){};
    virtual void m1_estop_pressed(){};
    virtual void m2_estop_pressed(){};
};
