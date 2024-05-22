#pragma once

enum class Event {
    LSAblocked = 0,
    LSAfree = 1,
    LSWblocked = 2,
    LSWfree = 3,
    LSRblocked = 4,
    LSRfree = 5,
    LSEblocked = 6,
    LSEfree = 7,
    StartPressed = 8,
    StartReleased = 9,
    StopPressed = 10,
    StopReleased = 11,
    ResetPressed = 12,
    ResetReleased = 13,
    EStopPressed = 14,
    EStopReleased = 15,
    InHightmeasurement = 16,
    leftHightmeasurement = 17,
    MetalDetected = 18
};
int dispatcherThread(int*);
void decodeMsg(int msg);
