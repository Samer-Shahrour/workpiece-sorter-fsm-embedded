#pragma once
#include "BaseStateEnd.h"

class Wait_for_info_End : public BaseStateEnd {
    void m2_lbe_blocked() override;

    void error() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};
