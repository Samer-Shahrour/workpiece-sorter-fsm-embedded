#pragma once
#include "BaseStateStop.h"

class IdleStop : public BaseStateStop {

public:
    void error() override;
    void stop_pressed() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void m2_lbe_blocked() override;
};
