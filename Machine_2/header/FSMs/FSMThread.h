#pragma once
#include <sys/neutrino.h>
#include <thread>
#include "../../header/PulseCodes.h"
#include "../../header/ChannelUtils.h"
#include "../../header/FSMs/Modes/ContextModes.h"
#include "../../header/Hal/Sensors.h"

void FSM_Thread(int, int, int);
