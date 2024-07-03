#include "../../../header/FSMs/StopFSM/StopError.h"
#include "../../../header/FSMs/StopFSM/IdleStop.h"
#include "../../../header/FSMs/StopFSM/EstopStop.h"

void StopError::error_ok() {
    new(this) IdleStop;
}

void StopError::m1_estop_pressed() {
    new(this) EstopStop;
}
void StopError::m2_estop_pressed() {
    new(this) EstopStop;
}

void StopError::m1_lbe_free(){
	new(this) IdleStop;
}
