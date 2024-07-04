#pragma once
#include "BaseStateEnd.h"

class Wait_for_ACK : public BaseStateEnd{
public:

    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void m1_lbe_blocked() override;
    void m2_lbb_blocked() override;
    void error() override;
};
