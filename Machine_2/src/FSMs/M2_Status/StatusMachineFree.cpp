#include "../../../header/FSMs/M2_Status/StatusError.h"
#include "../../../header/FSMs/M2_Status/StatusEstop.h"
#include "../../../header/FSMs/M2_Status/StatusMachineFree.h"
#include "../../../header/FSMs/M2_Status/StatusStop.h"
#include "../../../header/FSMs/M2_Status/StatusMachineNotFree.h"

void StatusMachineFree::m1_estop_pressed() {
    actions->sendNotOk();

    new (this) StatusEstop;
}

void StatusMachineFree::m2_estop_pressed() {
    actions->sendNotOk();
    ;
    new (this) StatusEstop;
}

void StatusMachineFree::stop_pressed() {
    actions->sendNotOk();

    new (this) StatusStop;
}

void StatusMachineFree::lbb_blocked() {
    //actions->sendNotOk(); //muss nicht unbedingt aber ok
    new (this) StatusMachineNotFree;
}

void StatusMachineFree::error() {
    actions->sendNotOk();
    new (this) StatusError;
}