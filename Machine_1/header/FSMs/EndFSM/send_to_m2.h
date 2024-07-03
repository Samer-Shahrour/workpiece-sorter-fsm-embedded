#pragma once
#include "BaseStateEnd.h"

class Send_to_m2 : public BaseStateEnd {

public:
    void m1_lbe_free() override;
    void m1_estop_pressed()override;
    void m2_estop_pressed() override;
    void error()override;
};