
#pragma once

#include "BaseStateBegin.h"

class Wait_for_wp : public BaseStateBegin {

    void m2_lbb_free() override;
    void error() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;

};


