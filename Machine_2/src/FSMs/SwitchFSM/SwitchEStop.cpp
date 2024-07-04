#include "../../../header/FSMs/SwitchFSM/SwitchEStop.h"

#include "../../../header/FSMs/SwitchFSM/SwitchIdle.h"

void SwitchEStop::estop_ok() {
    new(this) SwitchIdle;
}
