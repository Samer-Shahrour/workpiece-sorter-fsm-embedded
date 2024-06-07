#include "../../../header/FSMs/E_Stop/EStop_at_M1.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M2.h"
#include "../../../header/FSMs/E_Stop/Wait_for_typ.h"
#include "../../../header/FSMs/E_Stop/Metal_WP.h"
#include "../../../header/FSMs/E_Stop/Not_metal.h"

void Wait_for_typ::m1_estop_pressed() {
    actions->motorBlock();
    actions->turnYellow(true);
    actions->startRedFLASH();
    //done
	new(this) EStop_at_M1;
}

void Wait_for_typ::m2_estop_pressed(){
    actions->startRedFLASH();
    actions->motorBlock();
    //done
	new(this) EStop_at_M2;
}

void Wait_for_typ::m1_start_pressed(){
	actions->motorStart();
}

void Wait_for_typ::m1_stop_pressed(){
	actions->motorStop();
}

void Wait_for_typ::m1_lbs_blocked(){
	actions->sortOut();
	new(this) Not_metal;
}

void Wait_for_typ::m1_metal_detected(){
	actions->letThrough();
	new(this) Metal_WP;
}
