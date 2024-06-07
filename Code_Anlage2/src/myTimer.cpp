#include <time.h>
#include <signal.h>
#include <iostream>
#include <sys/neutrino.h>
#include <unistd.h>
#include "../header/myTimer.h"

using namespace std;

timer_t myStartTimer(int connectionID_Interrupt, short TIME_OUT_CODE, int value, bool period, uint64_t timeOutInMS) {
	timer_t timerid;
	struct sigevent sigEvent;
	struct itimerspec timer;

	SIGEV_PULSE_INIT(&sigEvent, connectionID_Interrupt, SIGEV_PULSE_PRIO_INHERIT, TIME_OUT_CODE, value);

	if(timer_create(CLOCK_REALTIME, &sigEvent, &timerid) != 0){
		perror("[Client] Timer creation failed");
	}

	uint64_t seconds = timeOutInMS / 1000;
	uint64_t nanoSeconds = (timeOutInMS % 1000) * 1000000;
	timer.it_value.tv_sec = seconds;
	timer.it_value.tv_nsec = nanoSeconds;

	if (period) {
	    timer.it_interval.tv_sec = seconds;
	    timer.it_interval.tv_nsec = nanoSeconds;
	} else {
	    timer.it_interval.tv_sec = 0;
	    timer.it_interval.tv_nsec = 0;
	}

	if(timer_settime(timerid, 0, &timer, NULL) != 0){ // Flag == 0 ---> relative Time  | Flag == TIMER_ABSTIME --> absolute Time
		perror("[Client] Setting timer failed");
		return(EXIT_FAILURE);
	}
	cout <<"[Client] Timer started" <<endl;
	return timerid;
}

void myDeleteTimer(timer_t timerid){
	 if(timer_delete(timerid) != 0){
		perror("[Client] Deleting timer failed");
	 }
}

void addTimeToTimer(timer_t timerid, uint64_t extraTimeInMS){
	struct itimerspec timer;
	if(timer_gettime(timerid,&timer) != 0){
		perror("[Client] Getting timer failed");
	}
	uint64_t seconds = extraTimeInMS / 1000;
	uint64_t nanoSeconds = (extraTimeInMS % 1000) * 1000000;
	timer.it_value.tv_sec += seconds;
	timer.it_value.tv_nsec += nanoSeconds;
}


