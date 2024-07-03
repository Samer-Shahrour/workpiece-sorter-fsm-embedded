#include "../../header/Hal/ADCThread.h"
#include "../../header/ChannelUtils.h"
#include "../../header/PulseCodes.h"
#include <sys/neutrino.h>
using namespace std;

// Konstruktor
ADCThread::ADCThread() {
    adc = new ADC(tsc);
}

ADCThread::~ADCThread(){
    adc->adcDisable();
    adc->unregisterAdcISR();
    delete adc;
}
void ADCThread::heightMeasurement(int connectionID_encoder, int pulse){
    adc->registerAdcISR(connectionID_encoder, pulse);
}
void ADCThread::sample(){
    adc->sample();
}

void threadADC(int connectionID_encoder){
    ThreadCtl(_NTO_TCTL_IO, 0);
    ADCThread adcThread;
    adcThread.heightMeasurement(connectionID_encoder, PULSE_HIGHT);
    bool receiveRunning = true;
    while(receiveRunning){
        adcThread.sample();
        usleep(20 * 1000);
    }
}

