#pragma once
#include "BaseStateEnd.h"

class EndError : public BaseStateEnd{
public:
    void error_ok() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void m2_Ok() override;
    void m2_Nok() override;
};