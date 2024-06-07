
#include "../../header/Logik/ContextHeightMeasurement.h"
#include "../../header/ChannelUtils.h"
#include "../../header/PulseCodes.h"
#include <sys/neutrino.h>
using namespace std;


// Konstruktor
ContextHeightMeasurement::ContextHeightMeasurement() {
    adc = new ADC(tsc);

}

ContextHeightMeasurement::~ContextHeightMeasurement(){
	  adc->adcDisable();
	  adc->unregisterAdcISR();
	  delete adc;
}
void ContextHeightMeasurement::heightMeasurement(int connectionID_encoder, int pulse){
    adc->registerAdcISR(connectionID_encoder, pulse);
}
void ContextHeightMeasurement::sample(){
	adc->sample();
}

void threadADC(int channelID_ADC, int connectionID_encoder){
	ThreadCtl(_NTO_TCTL_IO, 0);
	ContextHeightMeasurement contextADC;
	 contextADC.heightMeasurement(connectionID_encoder, PULSE_HIGHT);
	 contextADC.sample();
	_pulse msg;
	 bool receiveRunning = true;
	    while(receiveRunning){
	        int recvid = myReceivePulse(channelID_ADC, &msg);
	        if (recvid > 0) {
	            continue;
	        }
	        switch(msg.code){
				case PULSE_STOP_THREAD:
					printf("Dispatcher Thread kill code received!\n");
					receiveRunning = false;
					break;
				case PULSE_HIGHT:

                    switch(msg.value.sival_int){

                        case 0:
                            printf("belt\n");
                            break;
                        case 1:
                            printf("Side\n");
                            break;
                        case 2:
                            printf("Flat\n");
                            break;

                        case 3:
                            printf("Wrong\n");
                            break;
                    }
					 
					 contextADC.adc->sample();
					 break;
	        }
	    }
}

