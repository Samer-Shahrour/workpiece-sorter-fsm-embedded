#pragma once
#include "BaseStateStop.h"

class Stop : public BaseStateStop{

public:
    void error() override;
    void start_pressed() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};
