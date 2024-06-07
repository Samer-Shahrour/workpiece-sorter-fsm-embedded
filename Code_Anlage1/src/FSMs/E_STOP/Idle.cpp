#include "../../../header/FSMs/E_Stop/Idle.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M1.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M2.h"
#include "../../../header/FSMs/E_Stop/Wait_for_typ.h"

void Idle::m1_estop_pressed() {
    actions->motorBlock();
    actions->turnYellow(true);
    actions->startRedFLASH();
    //done
	new(this) EStop_at_M1;
}

void Idle::m2_estop_pressed(){
    actions->startRedFLASH();
    actions->motorBlock();
    //done
	new(this) EStop_at_M2;
}

void Idle::m1_start_pressed(){
	actions->motorStart();
}

void Idle::m1_stop_pressed(){
	actions->motorStop();
}

void Idle::m1_lbb_blocked(){
	actions->motorStart();
	new(this) Wait_for_typ;
}
