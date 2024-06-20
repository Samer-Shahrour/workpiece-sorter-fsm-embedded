#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>

#include "../../header/PulseCodes.h"
#include "../../header/ChannelUtils.h"
#include "../../header/Hal/Actuators.h"
#include "../../header/Hal/Sensors.h"
#include "../../header/myTimer.h"

void handleFSMRequest(Actuators*, int);
bool turnLamp(Actuators *a, int lampID, bool on);

Actuators::Actuators(){
    gpio_bank_1 = mmap_device_io(GPIO_LENGTH, (uint64_t) GPIO_BANK_1);
    gpio_bank_2 = mmap_device_io(GPIO_LENGTH, (uint64_t) GPIO_BANK_2);
    isSwitch = checkSwitch();
    if(!isSwitch){
        printf("HAL: Auswerfer\n");
    } else{
        printf("HAL: Weiche\n");
    }
    out32((uintptr_t)(gpio_bank_2 + GPIO_OE), LED_SWITCH_ALL_OFF);
    this->resumeConveyorBelt();
    this->lampSwitchOff(RED);
    this->lampSwitchOff(YELLOW);
    this->lampSwitchOff(GREEN);
    this->stopConveyorBelt();
    this->ledSwitchOff(LED_Q1);
    this->ledSwitchOff(LED_Q2);
    this->ledSwitchOff(LED_START);
    this->ledSwitchOff(LED_RESET);
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

void Actuators::letThrough(void){
    if(isSwitch){
        out32((uintptr_t)(gpio_bank_1 + SET), SWITCH); // Weiche oeffnen
    } else {
        out32((uintptr_t) (gpio_bank_1 + CLEAR), SWITCH); // Auswerfer schliessen
    }
}

void Actuators::sortOut(void){
    if(isSwitch){
        out32((uintptr_t)(gpio_bank_1 + CLEAR), SWITCH); // Weiche schliessen
    } else {
        out32((uintptr_t) (gpio_bank_1 + SET), SWITCH); // Auswerfer oeffnen
    }
}

bool Actuators::checkSwitch(void){
	uintptr_t gpio_bank_0 = mmap_device_io(GPIO_LENGTH, (uint64_t) GPIO_BANK_0);
	uint32_t data = in32((uintptr_t) gpio_bank_0 + GPIO_DATA_IN);
	return ((data & SWITCH_CHECK) != SWITCH_CHECK);
}

void actuatorsThread(int connectionID_HalActuators,int channelID_HalActuators) {
    ThreadCtl(_NTO_TCTL_IO, 0);
    timer_t time;
    Actuators a;
    a.connectionID_HalActuators = connectionID_HalActuators;
    bool an = false;
    _pulse msg;
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

            case PULSE_TIME_SWITCH_OUT:
            	printf("pulse_time_out_switch \n");
                if(a.isSwitch){
                    a.sortOut();
                } else {
                    a.letThrough();
                }
                break;
        }
    }
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
        myStartTimer(time, connectionID_HalActuators, PULSE_TIME_OUT_FLASH, msgValue, true, ONE_HZ);
        break;

    case GREEN:
        myStartTimer(time, connectionID_HalActuators, PULSE_TIME_OUT_FLASH,msgValue, true, HALF_HZ);
        break;
    }

}

void Actuators::startSwitchTimer(){
    myStartTimer(&this->halTimer, connectionID_HalActuators, PULSE_TIME_SWITCH_OUT, SWITCH_SENSOR, false, 650);
}
void Actuators::restartSwitchTimer(){
    int remaining = getRemainingTimeInMS(halTimer);
    if(remaining == 0){
        printf("remaininig Time for switch was 0, so no timer restarted\n");
        return;
    }

    myStartTimer(&this->halTimer, connectionID_HalActuators, PULSE_TIME_SWITCH_OUT, SWITCH_SENSOR, false,
                                  remaining+550);

    std::cout << "restarted timer for switch: NEW remaining time: " << getRemainingTimeInMS(this->halTimer) << std::endl;
}

void Actuators::startEjectorTimer(){
	timer_t id;
    myStartTimer(&id,connectionID_HalActuators, PULSE_TIME_SWITCH_OUT, EJECTOR, false, 50);
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

        case SORT_OUT:
            a->sortOut();
            if(!a->isSwitch){
                a->startEjectorTimer();
            }
			break;

        case LET_THROUGH:
            a->letThrough();
            if(a->isSwitch){
                a->startSwitchTimer();
            }
        	break;

        case HM_SLOW:
            if(a->isSwitch){
                a->restartSwitchTimer();
            }
            break;
	}
}
