#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>

#include "../../header/PulseCodes.h"
#include "../../header/ChannelUtils.h"
#include "../../header/Hal/Actuators.h"
#include "../../header/myTimer.h"

void handleFSMRequest(Actuators*, int);
bool turnLamp(Actuators *a, int lampID, bool on);

Actuators::Actuators(){
    gpio_bank_1 = mmap_device_io(GPIO_LENGTH, (uint64_t) GPIO_BANK_1);
    gpio_bank_2 = mmap_device_io(GPIO_LENGTH, (uint64_t) GPIO_BANK_2);
    isSwitch = checkSwitch();
    out32((uintptr_t)(gpio_bank_2 + GPIO_OE), LED_SWITCH_ALL_OFF);
}

Actuators::~Actuators(){
    munmap_device_io(GPIO_BANK_1, GPIO_LENGTH);
    munmap_device_io(GPIO_BANK_2, GPIO_LENGTH);
}

void Actuators::moveConveyorBelt(int direction){
    stopConveyorBelt();
    out32((uintptr_t)(gpio_bank_1 + SET), direction);
}

void Actuators::stopConveyorBelt(void){
    out32((uintptr_t)(gpio_bank_1 + CLEAR), MOVE_LEFT);
    out32((uintptr_t)(gpio_bank_1 + CLEAR), MOVE_RIGHT);
}

void Actuators::moveConveyorBeltSlow(bool slow){
    if(slow){
        out32((uintptr_t) (gpio_bank_1 + SET), MOVE_SLOW);
    } else {
        out32((uintptr_t) (gpio_bank_1 + CLEAR), MOVE_SLOW);
    }
}

void Actuators::pauseConveyorBelt(void){
    out32((uintptr_t)(gpio_bank_1 + SET), STOP);
}

void Actuators::resumeConveyorBelt(void){
    out32((uintptr_t)(gpio_bank_1 + CLEAR), STOP);
}

void Actuators::ledSwitchOn(int led_id){
    out32((uintptr_t)(gpio_bank_2 + SET), led_id);
}

void Actuators::ledSwitchOff(int led_id){
    out32((uintptr_t)(gpio_bank_2 + CLEAR), led_id);
}

void Actuators::lampSwitchOn(int lamp_id){
    out32((uintptr_t)(gpio_bank_1 + SET), lamp_id);
}


void Actuators::lampSwitchOff(int lamp_id){
    out32((uintptr_t)(gpio_bank_1 + CLEAR), lamp_id);
}

bool Actuators::checkLampOn(int lamp_id){
	//TODO: check if true result
	uint32_t data = in32((uintptr_t) gpio_bank_1 + GPIO_DATA_OUT);
	return ((data & lamp_id) == lamp_id);
}

// kann wahrscheinlich weg
void Actuators::letThrough(void){
    if(isSwitch){
        out32((uintptr_t)(gpio_bank_1 + SET), SWITCH);
        usleep(1000*500); // TODO: interrupt => while LSW unterbrochen ist
        out32((uintptr_t) (gpio_bank_1 + CLEAR), SWITCH);
    }
}

// kann wahrscheinlich weg
void Actuators::sortOut(void){
    if(!isSwitch){
        out32((uintptr_t)(gpio_bank_1 + SET), SWITCH);
        usleep(100*500);
        out32((uintptr_t) (gpio_bank_1 + CLEAR), SWITCH);
    }
}

void Actuators::openSwitch(void){
    if(isSwitch){
        out32((uintptr_t)(gpio_bank_1 + SET), SWITCH); // Weiche Ã¶ffnen
    } else {
        out32((uintptr_t) (gpio_bank_1 + CLEAR), SWITCH); // Auswerfer schlieÃŸen
    }
}

void Actuators::closeSwitch(void){
    if(isSwitch){
        out32((uintptr_t)(gpio_bank_1 + CLEAR), SWITCH); // Weiche schlieÃŸen
    } else {
        out32((uintptr_t) (gpio_bank_1 + SET), SWITCH); // Auswerfer Ã¶ffnen
    }
}


bool Actuators::checkSwitch(void){
    uint32_t data = in32((uintptr_t) gpio_bank_1 + GPIO_DATA_OUT);
    //std::cout << ((data & SWITCH) != SWITCH) << std::endl;
    return ((data & SWITCH) != SWITCH);
}


void actuatorsThread(int connectionID_HalActuators,int channelID_HalActuators) {
    ThreadCtl(_NTO_TCTL_IO, 0);
    timer_t time;
    bool an = false;
    Actuators a;
    _pulse msg;
    int msgValue = msg.value.sival_int;
    bool receivingRunning = true;

    while (receivingRunning) {
        int recvid = myReceivePulse(channelID_HalActuators, &msg);
        if (recvid < 0) {
            continue;
        }

        switch(msg.code) {
            case PULSE_STOP_THREAD:
                printf("Thread kill code received!\n");
                receivingRunning = false;
                break;

            case PULSE_FROM_FSM_TO_HAL:
                printf("request angekommen\n");
            	handleFSMRequest(&a, msg.value.sival_int);
                break;

            case PULSE_FLASH_ON:
               a.lampSwitchOn(msg.value.sival_int);
                handleFlash(msg.value.sival_int, &time, connectionID_HalActuators);
                break;

            case PULSE_FLASH_OFF:
                myDeleteTimer(time);
                a.lampSwitchOff(msg.value.sival_int);
                break;

            case PULSE_TIME_OUT_FLASH:
                an = turnLamp(&a, msg.value.sival_int, an);
                break;
        }
    }
    printf("Actuators thread Done!\n");
}

bool turnLamp(Actuators *a, int lampID, bool on){
    if(on){
        a->lampSwitchOn(lampID);
        return false;
    } else {
        a->lampSwitchOff(lampID);
        return true;
    }
}

void handleFlash(int msgValue, timer_t* time, int connectionID_HalActuators){
    myDeleteTimer(*time);
    switch(msgValue){
    case RED:
        *time = myStartTimer(connectionID_HalActuators, PULSE_TIME_OUT_FLASH, msgValue, true, ONE_HZ);
        break;

    case GREEN:
        *time = myStartTimer(connectionID_HalActuators, PULSE_TIME_OUT_FLASH,msgValue, true, HALF_HZ);
        break;

    }

}

void handleFSMRequest(Actuators *a, int msgValue){
	switch(msgValue){

	    //FB
		case MOVE_RIGHT:
		case MOVE_LEFT:
			a->moveConveyorBelt(msgValue);
			break;
	    case STOP:
	        a->stopConveyorBelt();
	        break;


	    case BLOCK:
	        a->pauseConveyorBelt();
	        break;
        case UNBLOCK:
            a->resumeConveyorBelt();
	        break;


	    case MOTOR_FAST:
	        a->moveConveyorBeltSlow(FAST);
	        break;
	    case MOTOR_SLOW:
	        a->moveConveyorBeltSlow(SLOW);
	        break;


        //LED
		case LED_START + LIGHT_ON:
	    case LED_RESET + LIGHT_ON:
	    case LED_Q2 + LIGHT_ON:
        case LED_Q1 + LIGHT_ON:
			a->ledSwitchOn(msgValue - LIGHT_ON);
			break;


	    case LED_START + LIGHT_OFF:
        case LED_RESET + LIGHT_OFF:
        case LED_Q2 + LIGHT_OFF:
        case LED_Q1 + LIGHT_OFF:
            a->ledSwitchOff(msgValue);
	        break;


	    //LAMPEN
	    case RED + LIGHT_ON:
        case YELLOW + LIGHT_ON:
        case GREEN + LIGHT_ON:
            a->lampSwitchOn(msgValue - LIGHT_ON);
	        break;


	    case RED + LIGHT_OFF:
        case YELLOW + LIGHT_OFF:
        case GREEN + LIGHT_OFF:
            a->lampSwitchOff(msgValue);
	        break;
	}
}
