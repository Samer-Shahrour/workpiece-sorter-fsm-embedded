#pragma once
#include "../ContextData.h"

class EndActions{

private:
    void sendMsg(int);
public:
    int connectionID_Dispatcher;
    int connectionID_FSM;

    void motorBlock();
    void motorUnblock();
    void notifyFSMs();
    void deleteMaxTimer(ContextData* data);
    void sendM2_OK();
    void motorStop();
};
