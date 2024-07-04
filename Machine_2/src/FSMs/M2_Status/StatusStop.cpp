#include "../../../header/FSMs/M2_Status/StatusError.h"
#include "../../../header/FSMs/M2_Status/StatusEstop.h"
#include "../../../header/FSMs/M2_Status/StatusMachineFree.h"
#include "../../../header/FSMs/M2_Status/StatusStop.h"
#include "../../../header/FSMs/M2_Status/StatusMachineNotFree.h"

void StatusStop::m1_estop_pressed() {
    new(this) StatusEstop;
}

void StatusStop::m2_estop_pressed() {
    new(this) StatusEstop;
}

void StatusStop::error() {
    new(this) StatusError;
}

void StatusStop::start_pressed() {
    actions->sendOk();
    new (this) StatusMachineFree;
}


