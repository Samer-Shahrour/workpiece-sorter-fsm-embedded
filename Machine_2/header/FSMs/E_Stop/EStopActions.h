#pragma once
#include "../ContextData.h"
class EStopActions{

private:
    void sendMsg(int);
public:
    int connectionID_Dispatcher;
    int connectionID_FSM;
    void turnRed(bool);
    void sendEstopOK(void);
    void turnLEDQ2(bool);
    void startRedFLASH(void);
    void stopRedFLASH(void);
    void motorUnblock(void);
    void deleteAllTimer(ContextData *data);
    void resetAllData(ContextData *data);
    void resetMachineActions(void);
};
