
#include <sys/neutrino.h>
#include "../../../header/FSMs/M2_Status/StatusActions.h"
#include "../../../header/Hal/Actuators.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/PulseCodes.h"
#include "../../../header/variables.h"
#include <iostream>


void StatusActions::sendOk() {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_M2_STATUS, M2_OK);
}

void StatusActions::sendNotOk() {
    MsgSendPulse(connectionID_Dispatcher, -1, PULSE_M2_STATUS, M2_NOK);
}
