#pragma once

#include "BaseStateBegin.h"

class Wait_for_leave : public BaseStateBegin {

    void m2_lbb_blocked() override;
    void m2_lbe_free() override;
    void m2_lbc_blocked() override;
    void error() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;

};
