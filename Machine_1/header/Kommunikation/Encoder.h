#pragma once
#include <sys/neutrino.h>

//-------------------------EVENTS





//------------------------

void encodeAndSendMsg(unsigned int, int);
void encoderThread(int channelID_Encoder, int channelID_Dispatcher);

void operationMode(_pulse msg, int connectionID_Dispatcher);
void calibrationMode(_pulse msg, int connectionID_Dispatcher);

