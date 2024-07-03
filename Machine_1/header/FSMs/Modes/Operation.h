#pragma once
#include "BaseStateModes.h"

class Operation : public BaseStateModes{
public:
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};
