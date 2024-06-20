#include "../../../header/FSMs/BeginFSM/EstopBegin.h"
#include "../../../header/FSMs/BeginFSM/wait_for_wp.h"

void EstopBegin::estop_ok() {
    actions->turnGreen(true);
    new(this) Wait_for_wp;
}
