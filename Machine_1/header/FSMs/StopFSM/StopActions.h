#pragma once
#include "../ContextData.h"

class StopActions{

private:
    void sendMsg(int);
public:

    int connectionID_Dispatcher;
    int connectionID_FSM;

    void motorBlock(void);
    void motorUnblock(void);
    void deleteAllTimer(ContextData* data);
    void getRemainingTime(ContextData* data);
    void restartAllTimer(ContextData* data);
};
