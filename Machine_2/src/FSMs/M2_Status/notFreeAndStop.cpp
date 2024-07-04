
#include "../../../header/FSMs/M2_Status/StatusMachineNotFree.h"
#include "../../../header/FSMs/M2_Status/StatusError.h"
#include "../../../header/FSMs/M2_Status/StatusEstop.h"
#include "../../../header/FSMs/M2_Status/StatusMachineFree.h"
#include "../../../header/FSMs/M2_Status/notFreeAndStop.h"
#include "../../../header/FSMs/M2_Status/StatusStop.h"

void NotFreeAndStop::m2_estop_pressed() {
    new (this) StatusEstop;
}

void NotFreeAndStop::m1_estop_pressed() {
    new (this) StatusEstop;
}

void NotFreeAndStop::error() {
    new (this) StatusError;
}

void NotFreeAndStop::lbe_free() {
    new (this) StatusStop;
}

void NotFreeAndStop::lbc_blocked() {
    new (this) StatusStop;
}

void NotFreeAndStop::start_pressed() {
    new (this) StatusMachineNotFree;
}
