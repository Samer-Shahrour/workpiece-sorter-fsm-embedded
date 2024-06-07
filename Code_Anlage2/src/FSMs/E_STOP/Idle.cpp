#include "../../../header/FSMs/E_Stop/Idle.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M1.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M2.h"

void Idle::m1_estop_pressed() {
    actions->motorBlock();
    actions->startRedFLASH();
	new(this) EStop_at_M1;
}

void Idle::m2_estop_pressed(){
    actions->motorBlock();
    actions->turnYellow(true);
    actions->startRedFLASH();
	new(this) EStop_at_M2;
}
