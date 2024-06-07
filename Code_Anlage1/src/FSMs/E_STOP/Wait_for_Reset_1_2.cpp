#include "../../../header/FSMs/E_Stop/EStop_at_M2.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M1.h"
#include "../../../header/FSMs/E_Stop/Wait_for_Reset_1_2.h"
#include "../../../header/FSMs/E_Stop/Wait_for_Reset_2.h"
#include "../../../header/FSMs/E_Stop/Wait_for_Reset_1.h"

void Wait_for_Reset_1_2::m2_estop_pressed(){
    //done
    actions->startRedFLASH();
	new(this) EStop_at_M2;
}

void Wait_for_Reset_1_2::m1_estop_pressed(){
    //done
    actions->startRedFLASH();
    actions->turnYellow(true);
	new(this) EStop_at_M1;
}

void Wait_for_Reset_1_2::m2_reset_pressed(){
    //done
	new(this) Wait_for_Reset_1;
}

void Wait_for_Reset_1_2::m1_reset_pressed(){
    //done
    actions->turnYellow(false);
	new(this) Wait_for_Reset_2;
}

