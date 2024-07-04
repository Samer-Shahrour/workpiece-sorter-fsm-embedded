#pragma once

#include <cstdint>

#define GPIO_DATA_IN 0x138

#define GPIO_BANK_0 0x44E07000

#define GPIO_LENGTH 0x1000

#define LBB 0x4
#define LBS 0x20
#define LBC 0x8000
#define LBE 0x100000

#define BUTTON_START 0x400000
#define BUTTON_STOP 0x800000
#define BUTTON_RESET 0x4000000
#define E_STOP 0x8000000

#define SWITCH_CHECK 0x4000

#define IN_HIGHT_MEASUREMENT 0x10
#define IS_METAL 0x80

#define NUMER_RELEVANT_PINS 10
static int pinsOfInterest[10] = {E_STOP, BUTTON_START, BUTTON_RESET, BUTTON_STOP, IS_METAL, IN_HIGHT_MEASUREMENT, LBB, LBS, LBC, LBE};

class Sensors {
    private:
        uintptr_t gpio_bank_0;

    public:
        Sensors();
        ~Sensors();
        bool lightBarrierInterrupted(uint32_t lightbarrier);
        int buttonIsPressed(uint32_t button);
        int isMetal(void);
};

