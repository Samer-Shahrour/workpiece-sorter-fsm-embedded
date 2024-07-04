#pragma once
#include "BaseStateStatus.h"

class StatusMachineFree : public BaseStateStatus {
public:
    void lbb_blocked() override;
    void error() override;
    void stop_pressed() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};

