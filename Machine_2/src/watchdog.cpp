#include <sys/dispatch.h>
#include <iostream>
#include "../header/watchdog.h"
#include "../header/ChannelUtils.h"
#include "../header/PulseCodes.h"
#include "../header/Kommunikation/Client.h"
#include "../header/Hal/Sensors.h"

void heartbeatFromMaster(int connectionID_FSM) {
    ThreadCtl(_NTO_TCTL_IO, 0);
    int conid;
    bool connected = false;
    // Attempt to open a connection to the master
    while (!connected) {
        usleep(100 * 1000); // 100 milliseconds
        conid = name_open(ATTACH_POINT_M1, NAME_FLAG_ATTACH_GLOBAL);
        if (conid >= 0) {
            connected = true;
        }
    }
    while (connected) {
        usleep(5 * 1000); // 5 milliseconds
        if (TWO_MACHINES) {
            MsgSendPulse_r(conid, SIGEV_PULSE_PRIO_INHERIT, PULSE_CONNECTION_CHECK, 0);
        }
    }
    printf("Watchdog thread ended\n");
}
