#include "../../../header/FSMs/EndFSM/endError.h"
#include "../../../header/FSMs/EndFSM/endEstop.h"
#include "../../../header/FSMs/EndFSM/wait_for_info.h"
void EndError::error_ok() {

    new(this) Wait_for_info_End;
}
void EndError::m1_estop_pressed() {
    new(this) EndError;
}
void EndError::m2_estop_pressed() {
    new(this) EndError;
}

