#pragma once
#include "../BaseStateModes.h"

#define TIMER_START_BUTTON      90
#define TIMER_FB_TICK           91
#define TIMER_HS_TICK           92

class Wait_for_flat1 : public BaseStateModes {
public:
    void lbb_blocked() override;
    void lbb_free() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};

class Measuring_Belt1 : public BaseStateModes {
public:
    void hight_changed() override;
    void incrementSection() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};

class Hight_Measured1 : public BaseStateModes{
public:
    void hight_changed() override;
    void incrementSection() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};

class Measurement_Done1 : public BaseStateModes{
public:
    void lbs_blocked() override;
    void incrementSection() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};

class To_Chute : public BaseStateModes {
public:
    void lbc_blocked() override;
    void incrementSection() override;
    void m1_estop_pressed() override;
    void m2_estop_pressed() override;
};




