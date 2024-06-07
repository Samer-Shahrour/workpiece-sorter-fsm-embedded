#pragma once

#include "../../../header/FSMs/E_Stop/ContextDataEstop.h"
#include "../../../header/FSMs/E_Stop/EStopActions.h"
#include <iostream>
using namespace std;

class BaseStateEstop {
protected:
	EStopActions *actions;
public:
    virtual ~BaseStateEstop(){};
    void setActions(EStopActions *a){this->actions = a;};

    virtual void m1_reset_pressed(){};
    virtual void m1_estop_pressed() {};
    virtual void m1_estop_released(){};

    virtual void m2_reset_pressed(){};
    virtual void m2_estop_pressed(){};
    virtual void m2_estop_released(){};

    virtual void m1_lbb_blocked(){};
	virtual void m1_lbb_free(){};

	virtual void m1_lbs_blocked(){};
	virtual void m1_lbs_free(){};

	virtual void m1_lbc_blocked(){};

	virtual void m1_lbe_blocked(){};
	virtual void m1_lbe_free(){};

	virtual void m1_start_pressed(){};
	virtual void m1_stop_pressed(){};

	virtual void m1_metal_detected(){};
};
