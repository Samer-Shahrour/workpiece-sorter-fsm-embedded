#pragma once
#include "BaseStateStop.h"

class StopError : public BaseStateStop{

public:
    void error_ok() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void m2_lbe_free() override;
};
