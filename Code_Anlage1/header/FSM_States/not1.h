#pragma once
#include "../../header/Logik/BaseState.h"

class Not1 : public BaseState{
public:
    void showState() override;
    void m1_estop_released() override;
    void m2_estop_pressed() override;
};
