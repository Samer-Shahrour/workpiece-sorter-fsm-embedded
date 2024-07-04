#include <iostream>
#include "../../../header/FSMs/E_Stop/EStop_at_M2.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M1_and_M2.h"
#include "../../../header/FSMs/E_Stop/Wait_for_Reset_1_2.h"

void EStop_at_M2::m2_estop_released(){
    actions->stopRedFLASH();
    actions->turnRed(true);
    new(this) Wait_for_Reset_1_2;
}

void EStop_at_M2::m1_estop_pressed(){
	new(this) EStop_at_M1_and_M2;
}
