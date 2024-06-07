#pragma once
#include "../../header/Logik/BaseState.h"
#include "../ADC_Sources/ADC.h"
#include "../ADC_Sources/TSCADC.h"
void threadADC(int channelID_ADC, int connectionID_encoder);

class ContextHeightMeasurement{

private:


public:
    ContextHeightMeasurement();
    ~ContextHeightMeasurement();
    void heightMeasurement(int connectionID_encoder, int pulse);
    void sample();
    TSCADC tsc;
    ADC *adc;
};

