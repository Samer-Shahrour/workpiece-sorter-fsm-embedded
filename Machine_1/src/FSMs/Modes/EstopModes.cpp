#include "../../../header/FSMs/Modes/EstopModes.h"
#include "../../../header/FSMs/Modes/IdleModes.h"

void EstopModes::estop_ok() {
    new(this) IdleModes;
}
