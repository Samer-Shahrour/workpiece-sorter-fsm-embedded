
#pragma once
#include "../ADC_Sources/ADC.h"
#include "../ADC_Sources/TSCADC.h"
void threadADC(int connectionID_encoder);

class ADCThread{

private:


public:
    ADCThread();
    ~ADCThread();
    void heightMeasurement(int connectionID_encoder, int pulse);
    void sample();
    TSCADC tsc;
    ADC *adc;
};
