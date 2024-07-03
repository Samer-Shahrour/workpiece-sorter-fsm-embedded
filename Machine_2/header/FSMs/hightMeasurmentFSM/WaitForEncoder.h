#pragma once

#include "BaseStateHM.h"

class WaitforEncoder : public BaseStateHM{

public:
    void hight_changed(int hight);
    void m1_estop_pressed();
    void m2_estop_pressed();
    void error();
};
