#pragma once
#include "BaseStateStatus.h"

class NotFreeAndStop : public BaseStateStatus {
public:
    void error() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void start_pressed() override;
    void lbe_free() override;
    void lbc_blocked() override;
};

