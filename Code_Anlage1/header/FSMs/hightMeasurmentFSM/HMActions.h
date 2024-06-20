#pragma once

#include "../ContextData.h"


class HMActions{

private:
    void sendMsg(int);
public:

    int connectionID_Dispatcher;
    int connectionID_FSM;

    void motor_fast(bool);
    void notifyFSMs();

    void incrementSwitchTime();

    void startTimer(ContextData* data, int id);
    void deleteMaxTimer(ContextData* data, int id);

    void setWpType(ContextData* data, int id, int type);

    void deleteAllTimer(ContextData* data);
    void restartMaxTimer(ContextData *data, int id);
    void getRemainingTime(ContextData* data, int id);
};
