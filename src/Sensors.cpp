#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>

#include "../header/Sensors.h"


Sensors::Sensors(){
	gpio_bank_0 = mmap_device_io(GPIO_LENGTH, (uint64_t) GPIO_BANK_0);
}

Sensors::~Sensors(){
	//TODO: prüfen, ob das richtig ist...
	munmap_device_io(GPIO_BANK_0, GPIO_LENGTH);
}

bool Sensors::lightBarrierInterrupted(uint32_t lightbarrier){
	uint32_t data = in32((uintptr_t) gpio_bank_0 + GPIO_DATA_IN);
	return ((data & lightbarrier) != lightbarrier);
}

int Sensors::buttonIsPressed(uint32_t button){
	uint32_t data = in32((uintptr_t) gpio_bank_0 + GPIO_DATA_IN);
	if(button == E_STOP || button == BUTTON_STOP){
		return ((data & button) != button);
	} else {
		return ((data & button) == button);
	}
}

bool Sensors::isUnderHS(void){
    return false; //TODO
}

int Sensors::isMetal(void){
	uint32_t data = in32((uintptr_t) gpio_bank_0 + GPIO_DATA_IN);
	return ((data & SENSOR_METAL) == SENSOR_METAL);
}


