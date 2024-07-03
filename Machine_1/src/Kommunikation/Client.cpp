#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <iostream>
#include <thread>
#include <sys/neutrino.h>
#include <unistd.h>


#include <sys/mman.h>
#include <hw/inout.h>
#include "../../header/Kommunikation/Client.h"
using namespace std;

void client(_pulse msg){
    if(TWO_MACHINES) {
        int conid;
        if ((conid = name_open(ATTACH_POINT_M1, NAME_FLAG_ATTACH_GLOBAL)) < 0) {   // important!! if server is running with "NAME_FLAG_ATTACH_GLOBAL" flag, you hae to use it here too
            perror("[Client] name_open failed");
        }
        //// ======== send pulse message ================

        if (MsgSendPulse_r(conid, SIGEV_PULSE_PRIO_INHERIT, msg.code, msg.value.sival_int) != 0) {
            perror("[Client]: sendPulse failed");
        }
        //// ======== close connection ================
        if (name_close(conid) != 0) {
            perror("[Client] name_close failed");
        }
    }
}
