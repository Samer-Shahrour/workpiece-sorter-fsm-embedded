#pragma once
#include "BaseStateStatus.h"

class StatusStop : public BaseStateStatus {
    void start_pressed() override;
    void error() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};
