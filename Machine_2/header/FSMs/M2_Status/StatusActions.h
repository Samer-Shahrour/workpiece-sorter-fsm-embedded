#pragma once

#include "../ContextData.h"

class StatusActions{

public:
    int connectionID_Dispatcher;
    void sendOk();
    void sendNotOk();
};
