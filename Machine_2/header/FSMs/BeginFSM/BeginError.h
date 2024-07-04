#pragma once
#include "BaseStateBegin.h"

class BeginError : public BaseStateBegin{

public:
    void error_ok() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};
