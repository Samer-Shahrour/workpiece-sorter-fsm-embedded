#pragma once
#include "../ContextData.h"

class EndActions{

private:
    void sendMsg(int);

public:
    int connectionID_Dispatcher;
    int connectionID_FSMs;
    void notifyFSMs();
    void motor_block();
    void motor_stop();
    void motor_unblock();
    void sendMsgTOM2(ContextData *data, int id);
    void deleteAllTimer(ContextData* data);
    void getRemainingTime(ContextData* data);
    void restartAllTimer(ContextData* data);
};
