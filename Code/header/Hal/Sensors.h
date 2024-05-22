#pragma once

#include <cstdint>

#define GPIO_DATA_IN 0x138

#define GPIO_BANK_0 0x44E07000

#define GPIO_LENGTH 0x1000

#define LSA 0x4
#define LSH 0x8
#define LSW 0x20
#define LSR 0x8000
#define LSE 0x100000

#define BUTTON_START 0x400000
#define BUTTON_STOP 0x800000
#define BUTTON_RESET 0x4000000
#define E_STOP 0x8000000

#define HIGHT_MEASUREMENT 0x10
#define SENSOR_METAL 0x80

#define NUMER_RELEVANT_PINS 10
static int pinsOfInterest[10] = {E_STOP, BUTTON_START, BUTTON_RESET, BUTTON_STOP, SENSOR_METAL, HIGHT_MEASUREMENT, LSA, LSW, LSR, LSE};

class Sensors {
    private:
        uintptr_t gpio_bank_0;

    public:
        Sensors();
        ~Sensors();
        bool lightBarrierInterrupted(uint32_t lightbarrier);
        int buttonIsPressed(uint32_t button);
        bool isUnderHS(void);
        int isMetal(void);
};

