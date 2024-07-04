#pragma once
#include "../BaseStateModes.h"

class Wait_for_flat2 : public BaseStateModes{
public:
    void lbb_blocked() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};

class Measuring_Belt2 : public BaseStateModes{
public:
    void hight_changed() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};

class Hight_Measured2 : public BaseStateModes{
public:
    void hight_changed() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};

class Measurement_Done2 : public BaseStateModes {
public:
    void lbs_blocked() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};

class Let_Through : public BaseStateModes {
public:
    void lbe_blocked() override;
    void incrementSection() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};

