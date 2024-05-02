#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>

#include "../header/Actuators.h"


Actuators::Actuators(){
    gpio_bank_1 = mmap_device_io(GPIO_LENGTH, (uint64_t) GPIO_BANK_1);
    gpio_bank_2 = mmap_device_io(GPIO_LENGTH, (uint64_t) GPIO_BANK_2);
    isSwitch = checkSwitch();
    out32((uintptr_t)(gpio_bank_2 + GPIO_OE), LED_SWITCH_ALL_OFF);
}

Actuators::~Actuators(){
	//TODO: prüfen, ob das richtig ist...
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
		out32((uintptr_t)(gpio_bank_1 + SET), SWITCH);
		usleep(1000*500); // TODO: interrupt => while LSW unterbrochen ist
		out32((uintptr_t) (gpio_bank_1 + CLEAR), SWITCH);
	}
}

void Actuators::sortOut(void){
	if(!isSwitch){
		out32((uintptr_t)(gpio_bank_1 + SET), SWITCH);
		usleep(100*500);
		out32((uintptr_t) (gpio_bank_1 + CLEAR), SWITCH);
	}
}

bool Actuators::checkSwitch(void){
	uint32_t data = in32((uintptr_t) gpio_bank_1 + GPIO_DATA_OUT);
	std::cout << ((data & SWITCH) != SWITCH) << std::endl;
	return ((data & SWITCH) != SWITCH);
}
