#include "../../../header/FSMs/hightMeasurmentFSM/EstopHM.h"
#include "../../../header/FSMs/hightMeasurmentFSM/WaitForEncoder.h"

void EstopHM::estop_ok() {
    new(this) WaitforEncoder;
}
