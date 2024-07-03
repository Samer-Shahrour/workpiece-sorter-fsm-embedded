#pragma once
#include "BaseStateEnd.h"

class M2_free : public BaseStateEnd{
public:

    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void m1_lbe_free() override;
    void m2_Nok() override;
    void error() override;
};
