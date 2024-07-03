#include "../../../header/FSMs/E_Stop/Idle.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M1.h"
#include "../../../header/FSMs/E_Stop/EStop_at_M2.h"

void Idle::m1_estop_pressed() {
    actions->resetMachineActions();
    actions->startRedFLASH();
    actions->deleteAllTimer(data);
    actions->resetAllData(data);
    new(this) EStop_at_M1;
}

void Idle::m2_estop_pressed(){
    actions->resetMachineActions();
    actions->startRedFLASH();
    actions->deleteAllTimer(data);
    actions->resetAllData(data);
    actions->turnLEDQ2(true);
    new(this) EStop_at_M2;
}
