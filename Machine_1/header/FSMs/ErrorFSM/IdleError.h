#pragma once
#include "BaseStateError.h"

class IdleError : public BaseStateError {

public:
    void error() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};