#pragma once
#include "BaseStateEnd.h"

class EndIdle : public BaseStateEnd{
public:

    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void m1_lbe_blocked() override;
    void error() override;
    void m2_Ok() override;
    void m2_Nok() override;
};
