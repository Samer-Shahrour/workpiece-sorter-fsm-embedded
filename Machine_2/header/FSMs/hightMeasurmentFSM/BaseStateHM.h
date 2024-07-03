#pragma once

#include <iostream>
#include "HMActions.h"
#include "../ContextData.h"
#include "HMActions.h"
using namespace std;

class BaseStateHM {
protected:
     HMActions *actions;
     ContextData *data;
public:
    virtual ~BaseStateHM(){};
    void setActions(HMActions *a){this->actions = a;};
    void setData(ContextData *d){this->data = d;};
    virtual void hight_changed(int hight){};
    virtual void error(){};
    virtual void error_ok(){};
    virtual void estop_ok(){};
    virtual void m1_estop_pressed(){};
    virtual void m2_estop_pressed(){};



};
