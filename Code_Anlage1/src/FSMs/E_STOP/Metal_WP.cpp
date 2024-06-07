#include "../../../header/FSMs/E_Stop/EStop_at_M1.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M2.h"
#include "../../../header/FSMs/E_Stop/Wait_for_end.h"
#include "../../../header/FSMs/E_Stop/Metal_WP.h"
#include "../../../header/FSMs/E_Stop/Not_metal.h"
#include "../../../header/FSMs/E_Stop/Idle.h"

void Metal_WP::m1_estop_pressed() {
    actions->motorBlock();
    actions->turnYellow(true);
    actions->startRedFLASH();
    //done
	new(this) EStop_at_M1;
}

void Metal_WP::m2_estop_pressed(){
    actions->startRedFLASH();
    actions->motorBlock();
    //done
	new(this) EStop_at_M2;
}

void Metal_WP::m1_start_pressed(){
	actions->motorStart();
}

void Metal_WP::m1_stop_pressed(){
	actions->motorStop();
}

void Metal_WP::m1_lbe_blocked(){
	actions->motorBlock();
	new(this) Wait_for_end;
}

