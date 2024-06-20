#pragma once
#include "BaseStateSwitch.h"

class MetalDetected : public BaseStateSwitch {

public:
    void lbc_blocked() override;
    void lbc_free() override;
    void lbs_free() override;
    void error() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
    void metal_detected() override;
};
