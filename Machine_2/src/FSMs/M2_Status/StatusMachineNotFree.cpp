
#include "../../../header/FSMs/M2_Status/StatusMachineNotFree.h"
#include "../../../header/FSMs/M2_Status/StatusError.h"
#include "../../../header/FSMs/M2_Status/StatusEstop.h"
#include "../../../header/FSMs/M2_Status/StatusMachineFree.h"
#include "../../../header/FSMs/M2_Status/notFreeAndStop.h"

void StatusMachineNotFree::stop_pressed() {
    new(this) NotFreeAndStop;
}
void StatusMachineNotFree::m2_estop_pressed() {
    new(this) StatusEstop;
}
void StatusMachineNotFree::m1_estop_pressed() {
    new(this) StatusEstop;
}
void StatusMachineNotFree::error() {
    new(this) StatusError;
}
void StatusMachineNotFree::lbc_blocked() {
	actions->sendOk();
    new(this) StatusMachineFree;
}
void StatusMachineNotFree::lbe_free() {
	actions->sendOk();
    new(this) StatusMachineFree;
}
