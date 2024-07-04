#pragma once
#include "BaseStateStatus.h"
class StatusMachineNotFree : public BaseStateStatus {
public:
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void error() override;
    void lbe_free() override;
    void lbc_blocked() override;
    void stop_pressed() override;
};
