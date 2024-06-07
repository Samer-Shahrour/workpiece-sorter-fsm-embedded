#pragma once
#include "../../header/Logik/BaseState.h"


class Reset : public BaseState {
public:
    void showState() override;

    void m1_estop_pressed() override;

    void m2_estop_pressed() override;

    void m1_reset_pressed() override;

};