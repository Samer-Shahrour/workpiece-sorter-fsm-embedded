#pragma once
#include "BaseStateEnd.h"

class M2_not_free : public BaseStateEnd{
public:
    void error() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void m2_lbb_blocked() override;
    void m1_lbe_free() override;
    void m2_Ok() override;
};
