#include "../../../header/FSMs/EndFSM/endIdle.h"
#include "../../../header/FSMs/EndFSM/endError.h"
#include "../../../header/FSMs/EndFSM/endEstop.h"


void EndError::error_ok() {
    new(this) EndIdle;
}

void EndError::m1_estop_pressed() {
    new(this) EndEstop;
}

void EndError::m2_estop_pressed() {
    new(this) EndEstop;
}

void EndError::m2_Ok() {
    data->m2_free = true;
}

void EndError::m2_Nok() {
    data->m2_free = false;
}
