#include "../../../header/FSMs/ErrorFSM/EstopError.h"
#include "../../../header/FSMs/ErrorFSM/IdleError.h"

void EstopError::estop_ok() {
    actions->turnGreen(true);
    new(this) IdleError;
}
