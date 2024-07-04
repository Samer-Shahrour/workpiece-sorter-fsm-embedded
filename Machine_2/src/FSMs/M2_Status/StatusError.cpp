#include "../../../header/FSMs/M2_Status/StatusError.h"
#include "../../../header/FSMs/M2_Status/StatusEstop.h"
#include "../../../header/FSMs/M2_Status/StatusMachineFree.h"

void StatusError::m1_estop_pressed() {
    new (this) StatusEstop;
}

void StatusError::m2_estop_pressed() {
    new (this) StatusEstop;
}

void StatusError::error_ok() {
    actions->sendOk();
    new (this) StatusMachineFree;
}