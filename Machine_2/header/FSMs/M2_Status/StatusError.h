#pragma once
#include "BaseStateStatus.h"
class StatusError : public BaseStateStatus {
public:
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void error_ok() override;
};
