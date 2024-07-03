#pragma once
#include "../ContextData.h"

class BeginActions{

private:
    void sendMsg(int);
public:
    int connectionID_Dispatcher;
    int connectionID_FSM;

    void motorStart();
    void notifyFSMs();
    void startTransferTimer(ContextData* data);
    void deleteTransferTimer(ContextData* data);
    void pushObject(ContextData* data);
    void startWPTimer(ContextData* data);
};
