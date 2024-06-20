#pragma once
#define ONE_HZ 1000
#define HALF_HZ 500
#define S_TO_MS 1000
#define NS_TO_MS 1000000

long long createTimeStamp(void);
void myStartTimer(timer_t* timerid, int connectionID_Interrupt, short TIME_OUT_CODE, int value, bool period, uint64_t timeOutInMS);
void myDeleteTimer(timer_t timerid);
uint64_t getRemainingTimeInMS(timer_t timerid);
