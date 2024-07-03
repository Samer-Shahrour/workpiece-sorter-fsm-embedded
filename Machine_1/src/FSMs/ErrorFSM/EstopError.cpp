#include "../../../header/FSMs/ErrorFSM/EstopError.h"
#include "../../../header/FSMs/ErrorFSM/IdleError.h"

void EstopError::estop_ok() {

    new(this) IdleError;
}
