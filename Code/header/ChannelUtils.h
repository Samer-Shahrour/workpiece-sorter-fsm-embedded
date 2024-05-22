#pragma once


int myCreateChannel(void);
int myConnectAttach(int);
int myReceivePulse(int, _pulse *);
void myConnectDetach(int);
void myChannelDestroy(int);
void myConnectDetach(int);