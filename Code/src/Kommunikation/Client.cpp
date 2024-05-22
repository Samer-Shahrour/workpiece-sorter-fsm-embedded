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

#define ATTACH_POINT "server"

thread clientGNS;

void client(){
	system("gns -c");
	int conid;
	if((conid = name_open(ATTACH_POINT, NAME_FLAG_ATTACH_GLOBAL)) < 0){   // important!! if server is running with "NAME_FLAG_ATTACH_GLOBAL" flag, you hae to use it here too
		perror("[Client] name_open failed");

	}
	std::cout << "[Client] Opened name and connected to channel\n";
	//// ======== send pulse message ================

	 if(MsgSendPulse(conid,SIGEV_PULSE_PRIO_INHERIT,_PULSE_CODE_MINAVAIL+10,0x10000) != 0){ //rote ampel
		perror("[Client]: sendPulse failed");
		exit(EXIT_FAILURE);
	 }

	 //// ======== close connection ================
	 if(name_close(conid) != 0){
		perror("[Client] name_close failed");
	}
}
