#pragma once
#include "BaseStateHM.h"

class ErrorHM : public BaseStateHM{

public:
    void error_ok() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};
