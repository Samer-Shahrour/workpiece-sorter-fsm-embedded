#pragma once
#define ONE_HZ 1000
#define HALF_HZ 500

timer_t myStartTimer(int connectionID_Interrupt, short TIME_OUT_CODE, int value, bool period, uint64_t timeOutInMS);
void myDeleteTimer(timer_t timerid);
void addTimeToTimer(timer_t timerid, uint64_t extraTimeInMS);
