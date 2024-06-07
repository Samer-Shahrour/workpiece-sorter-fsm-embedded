#pragma once

#include "../../header/Logik/ContextData.h"
#include <iostream>
using namespace std;

class BaseState {
protected:
    ContextData *data;
public:
    virtual ~BaseState(){};
    void setData(ContextData *data){this->data = data;};
    virtual void showState(){};

    //Machine 1
    virtual void m1_lbb_blocked(){};
    virtual void m1_lbb_free(){};
    virtual void m1_lbs_blocked(){};
    virtual void m1_lbs_free(){};
    virtual void m1_lbc_blocked(){};
    virtual void m1_lbc_free(){};
    virtual void m1_lbe_blocked(){};
    virtual void m1_lbe_free(){};
    virtual void m1_start_pressed(){};
    virtual void m1_start_released(){};
    virtual void m1_stop_pressed(){};
    virtual void m1_stop_released(){};
    virtual void m1_reset_pressed(){};
    virtual void m1_reset_released(){};
    virtual void m1_estop_pressed() {};
    virtual void m1_estop_released(){};
    virtual void m1_in_hight_measurement() {};
    virtual void m1_left_hight_measurement() {};
    virtual void m1_metal_detected() {};

    //Machine 2
    virtual void m2_lbc_blocked(){};
    virtual void m2_lbc_free(){};
    virtual void m2_lbe_blocked(){}; //-> wahrscheinlich nicht nötig
    virtual void m2_lbe_free(){};
    virtual void m2_start_pressed(){};
    virtual void m2_start_released(){};
    virtual void m2_estop_pressed(){};
    virtual void m2_estop_released(){};

};
