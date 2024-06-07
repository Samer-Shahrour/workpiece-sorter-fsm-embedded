#include "../../../header/FSMs/E_Stop/EStop_at_M2.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M1.h"
#include "../../../header/FSMs/E_Stop/Wait_for_Reset_2.h"
#include "../../../header/FSMs/E_Stop/Idle.h"

void Wait_for_Reset_2::m2_estop_pressed(){
    //done
    //damit es sync bleibt?
    actions->startRedFLASH();
	new(this) EStop_at_M2;
}

void Wait_for_Reset_2::m1_estop_pressed(){
    //done
    actions->startRedFLASH();
    actions->turnYellow(true);
	new(this) EStop_at_M1;
}

void Wait_for_Reset_2::m2_reset_pressed(){
    //done
	actions->motorStop();
    actions->motorUnblock();
    actions->turnRed(false);
	new(this) Idle;
}

