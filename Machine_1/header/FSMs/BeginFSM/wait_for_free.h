#pragma once
#include "BaseStateBegin.h"

class Wait_for_free : public BaseStateBegin {

public:
    void m1_lbb_free() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void externer_error() override;
};