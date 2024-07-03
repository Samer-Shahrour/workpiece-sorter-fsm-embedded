#include "../../../header/FSMs/M2_Status/StatusMachineFree.h"
#include "../../../header/FSMs/M2_Status/StatusEstop.h"

void StatusEstop::estop_ok() {
    actions->sendOk();
    new(this) StatusMachineFree;
}
