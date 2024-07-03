#include <time.h>
#include <signal.h>
#include <iostream>
#include <sys/neutrino.h>
#include <unistd.h>
#include "../header/myTimer.h"


using namespace std;

uint64_t createTimeStamp(){
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    long seconds = time.tv_sec;
    long nano = time.tv_nsec;
    uint64_t milliseconds = (seconds * 1000) + (nano / 1000000);
    return milliseconds;
}

void myStartTimer(timer_t* timerid, int connectionID_Interrupt, short TIME_OUT_CODE, int value, bool period, uint64_t timeOutInMS) {
	if(timeOutInMS > 5000){
		timeOutInMS = 4000;
	}
	struct sigevent sigEvent;
	struct itimerspec timer;
	SIGEV_PULSE_INIT(&sigEvent, connectionID_Interrupt, SIGEV_PULSE_PRIO_INHERIT, TIME_OUT_CODE, value);

	if(timer_create(CLOCK_REALTIME, &sigEvent, timerid) != 0){
		//perror("[Client] Timer creation failed\n");
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

	if(timer_settime(*timerid, 0, &timer, NULL) != 0){ // Flag == 0 ---> relative Time  | Flag == TIMER_ABSTIME --> absolute Time
		exit(EXIT_FAILURE);
	}
}

void myDeleteTimer(timer_t timerid) {
    struct itimerspec timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_nsec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_nsec = 0;
    timer_settime(timerid, 0, &timer, NULL);

    /*
	 if(timer_delete(timerid) != 0){
		//perror("[Client] Deleting timer failed\n");
	 }
     */
}

uint64_t getRemainingTimeInMS(timer_t timerid){
	struct itimerspec timer;
	if(timer_gettime(timerid,&timer) != 0){
		return 0;
	}
	uint64_t seconds = timer.it_value.tv_sec;
	uint64_t nanoSeconds = timer.it_value.tv_nsec;
	uint64_t milliSeconds = ((seconds * S_TO_MS) + (nanoSeconds / NS_TO_MS));
	return milliSeconds;
}




