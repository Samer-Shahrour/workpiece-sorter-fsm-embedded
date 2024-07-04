#pragma once
#include "BaseStateSwitch.h"

class SwitchIdle : public BaseStateSwitch {
public:
    void error() override;
    void handleWrongWP(ContextData *data);
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void lbs_blocked() override;
    void lbc_blocked() override;
    void lbc_free() override;
    void metal_detected() override;
};
