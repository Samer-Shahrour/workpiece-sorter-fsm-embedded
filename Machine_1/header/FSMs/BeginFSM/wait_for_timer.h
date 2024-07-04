#pragma once
#include "BaseStateBegin.h"

class Wait_for_timer : public BaseStateBegin {

public:
    void m1_lbb_blocked() override;
    void time_out_begin() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void externer_error() override;
};