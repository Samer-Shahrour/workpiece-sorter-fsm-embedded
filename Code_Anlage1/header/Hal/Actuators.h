#pragma once
#include <time.h>
#include <cstdint>
#define GPIO_DATA_OUT 0x13C
#define GPIO_OE 0x134

#define GPIO_BANK_1 0x4804C000
#define GPIO_BANK_2 0x481AC000

#define GPIO_LENGTH 0x1000

//Lamps
#define RED 0x10000
#define YELLOW 0x20000
#define GREEN 0x40000

//LED
#define LED_START 0x4
#define LED_RESET 0x8
#define LED_Q1 0x10
#define LED_Q2 0x20
#define LED_SWITCH_ALL_OFF 0x0

//Conveyor Belt
#define MOVE_RIGHT 0x1000
#define MOVE_LEFT 0x2000
#define MOVE_SLOW 0x4000
#define STOP 0x8000

#define SWITCH 0x80000

#define FAST false
#define SLOW true


//events for Thread
#define BLOCK 0x13
#define UNBLOCK 0x14
#define LIGHT_ON 0x15
#define LIGHT_OFF 0x00
#define MOTOR_FAST 0x11
#define MOTOR_SLOW 0x12
#define SORT_OUT 0x16
#define LET_THROUGH 0x17

void handleFlash(int msgValue, timer_t* time,int connectionID_HalActuators);
void actuatorsThread(int connectionID_HalActuators,int channelID_HalActuators);
class Actuators {
private:
    uintptr_t gpio_bank_1;
    uintptr_t gpio_bank_2;
    bool isSwitch;
    const int SET = 0x194;
    const int CLEAR = 0x190;
    bool checkSwitch(void);
public:
    Actuators(void);
    ~Actuators(void);
    void moveConveyorBelt(int direction);
    void moveConveyorBeltSlow(bool slow);
    void stopConveyorBelt(void);
    void pauseConveyorBelt(void);
    void resumeConveyorBelt(void);
    void ledSwitchOn(int led_id);
    void ledSwitchOff(int led_id);
    void lampSwitchOn(int lamp_id);
    void lampSwitchOff(int lamp_id);

    bool checkLampOn(int lamp_id);
    void closeSwitch(void);
    void openSwitch(void);

    void letThrough(void); 	// -> kann wahrscheinlich weg
    void sortOut(void);		// -> kann wahrscheinlich weg
};
