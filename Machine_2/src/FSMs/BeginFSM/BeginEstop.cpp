#include "../../../header/FSMs/BeginFSM/BeginEstop.h"
#include "../../../header/FSMs/BeginFSM/wait_for_info.h"

void BeginEstop::estop_ok() {
    new(this) Wait_for_info_Begin;
}
