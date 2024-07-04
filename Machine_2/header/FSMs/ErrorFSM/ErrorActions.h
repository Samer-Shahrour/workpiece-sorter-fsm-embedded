#pragma once
#include "../ContextData.h"
class ErrorActions{

private:
    void sendMsg(int);
public:

    int connectionID_Dispatcher;
    int connectionID_FSM;

    void turnAllOff(void);
    void turnGreen(bool);
    void startRedFLASH(void);
    void stopRedFLASH(void);
    void motorBlock(void);
    void motorUnblock(void);
    void motorStop(void);
    void sendErrorOK(void);
    void deleteAllTimer(ContextData *data);
    void sendM2_NOK();
    void sendM2_OK();
};
