#pragma once
#include "BaseStateModes.h"

class Wait_for_release : public BaseStateModes{
public:
    void m1_start_released() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void time_out_start() override;
};