#pragma once

#include "../../header/Logik/baseStateHightMeasurement.h"
#include <iostream>
using namespace std;

void hightMeasurementThread(int channelID_FSM_Hight_Measurement, int connectionID_Encoder, int connectionID_Dispatcher);

class ContextHightMeasurement {
private:
    BaseStateHightMeasurement *state;
    //ContextActions *data;
public:
    ContextHightMeasurement();
    virtual ~ContextHightMeasurement();

    void showState();
    void beltHight();
    void sideHight();
    void highWPHight();
    void flatWPHight();
    void holeHight();
    void otherHight();

};
