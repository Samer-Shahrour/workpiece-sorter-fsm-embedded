#include "../../../header/FSMs/EndFSM/endEstop.h"
#include "../../../header/FSMs/EndFSM/wait_for_info.h"

void EndEstop::estop_ok() {
    new(this) Wait_for_info_End;
}
