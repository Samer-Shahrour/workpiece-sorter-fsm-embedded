#pragma once
#include "BaseStateError.h"

class Error : public BaseStateError{
public:
    void reset_pressed() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};
