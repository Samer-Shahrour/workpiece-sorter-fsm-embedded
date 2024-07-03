#pragma once
#include "../ContextData.h"

class SwitchActions{

private:
    void sendMsg(int);
public:
    int connectionID_Dispatcher;
    int connectionID_FSM;
    void notifyFSMs(void);
    void deleteFromVector(ContextData* data, int id);
    void letThrough(void);
    void sortOut(void);
    void turnYellow(bool);
    void motorStop(void);
    void deleteMaxTimer(ContextData* data, int id);
};
