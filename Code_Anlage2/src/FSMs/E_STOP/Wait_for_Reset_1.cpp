#include "../../../header/FSMs/E_Stop/EStop_at_M2.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M1.h"
#include "../../../header/FSMs/E_Stop/Wait_for_Reset_1.h"
#include "../../../header/FSMs/E_Stop/Idle.h"

void Wait_for_Reset_1::m2_estop_pressed(){
    actions->startRedFLASH();
    actions->turnYellow(true);
	new(this) EStop_at_M2;
}

void Wait_for_Reset_1::m1_estop_pressed(){
	actions->startRedFLASH();
	new(this) EStop_at_M1;
}

void Wait_for_Reset_1::m1_reset_pressed(){
    actions->turnRed(false);
    actions->motorUnblock();
	new(this) Idle;
}

