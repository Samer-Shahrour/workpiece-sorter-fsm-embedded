#pragma once
#include "../ContextData.h"

class BeginActions{

private:
    void sendMsg(int);

public:
    int connectionID_Dispatcher;
    int connectionID_FSMs;
    void startTimerBegin(ContextData* data);
    void notifyFSMs();
    void sendEstopOK();
    void turnLEDQ1(bool);
    void pushObject(ContextData* data);
    void motorStart(void);
    void turnGreen(bool);
};
