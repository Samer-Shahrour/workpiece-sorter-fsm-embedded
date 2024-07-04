#pragma once
#include "BaseStateModes.h"
class IdleModes : public BaseStateModes{

public:
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void m1_start_pressed() override;
};
