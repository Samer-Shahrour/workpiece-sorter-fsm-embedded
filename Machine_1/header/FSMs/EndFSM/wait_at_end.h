#pragma once
#include "BaseStateEnd.h"

class Wait_At_End : public BaseStateEnd {

public:
    void m1_estop_pressed()override;
    void m2_estop_pressed() override;
    void error() override;
    void m1_lbe_blocked() override;
    void m2_Ok() override;
    void m2_Nok() override;
};