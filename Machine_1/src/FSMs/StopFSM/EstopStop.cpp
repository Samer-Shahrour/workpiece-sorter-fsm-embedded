#include "../../../header/FSMs/StopFSM/EstopStop.h"
#include "../../../header/FSMs/StopFSM/IdleStop.h"

void EstopStop::estop_ok() {
    new(this) IdleStop;
}
