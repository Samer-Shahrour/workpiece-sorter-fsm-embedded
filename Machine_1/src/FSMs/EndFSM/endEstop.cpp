#include "../../../header/FSMs/EndFSM/endEstop.h"
#include "../../../header/FSMs/EndFSM/endIdle.h"

void EndEstop::estop_ok() {
    new(this) EndIdle;
}
