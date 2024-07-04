#pragma once

#include "BaseStateEnd.h"

class Wait_for_gone : public BaseStateEnd {
    void m2_lbe_free() override;
    void error() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};


