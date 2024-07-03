#include <iostream>
#include <errno.h>
#include <thread>
#include <sys/neutrino.h>


int myCreateChannel(void){
    int channelID = ChannelCreate(0);
    if (channelID < 0) {
        printf("Could not create a channel in!\n");
        exit(EXIT_FAILURE);
    }
    return channelID;
}

int myConnectAttach(int channelID){
    int connectionID = ConnectAttach(0, 0, channelID, _NTO_SIDE_CHANNEL, 0);
    if (connectionID < 0) {
        printf("Could not connect to channel!\n");
        return EXIT_FAILURE;
    }
    return connectionID;
}

int myReceivePulse(int channelID, _pulse* msg){
    int recvid = MsgReceivePulse(channelID, msg, sizeof(_pulse), nullptr);
    if (recvid < 0) {
        printf("MsgReceivePulse failed!");
        exit(EXIT_FAILURE);
    }
    return recvid;
}

void myConnectDetach(int connectionID){
    int detach_status = ConnectDetach(connectionID);
    if (detach_status != EOK) {
        perror("Detaching channel failed!");
        exit(EXIT_FAILURE);
    }
}

void myChannelDestroy(int channelID){
    int destroy_status = ChannelDestroy(channelID);
    if (destroy_status != EOK) {
        perror("Destroying channel failed!");
        exit(EXIT_FAILURE);
    }
}


