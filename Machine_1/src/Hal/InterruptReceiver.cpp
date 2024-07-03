#include "../../header/Hal/InterruptReceiver.h"
#include "../../header/PulseCodes.h"
#include "../../header/Hal/Actuators.h"
#include "../../header/Hal/Sensors.h"
#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/mman.h>
#include <hw/inout.h>


int interruptID;

void getInterruptAbilities(){
    // Request interrupt and IO abilities
    int procmgr_status = procmgr_ability(
            0,
            PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
            PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
            PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
            PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
            PROCMGR_AID_EOL
    );
    if (procmgr_status != EOK) {
        perror("Requested abilities failed or denied!");
        exit(EXIT_FAILURE);
    }
}

void registerInterrupt(int connectionID_Interrupt){
    struct sigevent intr_event;
    SIGEV_PULSE_INIT(&intr_event, connectionID_Interrupt, SIGEV_PULSE_PRIO_INHERIT, PULSE_INTRRUPT, 0);
    interruptID = InterruptAttachEvent(INTR_GPIO_PORT0, &intr_event, 0);
    if (interruptID < 0) {
        perror("Interrupt was not able to be attached!");
        return exit(EXIT_FAILURE);
    }
}

void configureIRQStatus(uintptr_t gpio_bank_0){
    for(int pin = 0; pin < NUMER_RELEVANT_PINS; pin++){
        out32((uintptr_t) gpio_bank_0 + GPIO_IRQSTATUS_SET_1, pinsOfInterest[pin]);
    }
}

void enableRisingEdgeDetect(uintptr_t gpio_bank_0){
    unsigned int temp = in32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT));
    temp |= (E_STOP | BUTTON_START | BUTTON_RESET | BUTTON_STOP | IS_METAL | IN_HIGHT_MEASUREMENT | LBB | LBS | LBC | LBE);//Add desired pins.
    out32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT), temp);			//Write new config back.
}


void enableFallingEdgeDetect(uintptr_t gpio_bank_0){
    unsigned int temp = in32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT));			//Read current config.
    temp |= (E_STOP | BUTTON_START | BUTTON_RESET | BUTTON_STOP | IS_METAL | IN_HIGHT_MEASUREMENT | LBB | LBS | LBC | LBE);//Add desired pins.
    out32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT), temp);			//Write new config back.
}

void initInterrupt(int connectionID_ISR){
    getInterruptAbilities();
    InterruptEnable();
    uintptr_t gpio_bank_0 = mmap_device_io(GPIO_LENGTH, GPIO_BANK_0);
    registerInterrupt(connectionID_ISR);
    configureIRQStatus(gpio_bank_0);
    enableRisingEdgeDetect(gpio_bank_0);
    enableFallingEdgeDetect(gpio_bank_0);
}

void myInterruptDetach(int interruptID){
    int intr_detach_status = InterruptDetach(interruptID);
    if (intr_detach_status != EOK) {
        perror("Detaching interrupt failed!");
        exit(EXIT_FAILURE);
    }
}

void interruptThread(int channelID_Interrupt, int connectionID_Encoder) {
    ThreadCtl(_NTO_TCTL_IO, 0);


    _pulse msg;
    bool receivingRunning = true;

    while (receivingRunning) {
        int recvid = MsgReceivePulse(channelID_Interrupt, &msg, sizeof(_pulse), nullptr);

        if (recvid < 0) {
            perror("MsgReceivePulse failed!");
            exit(EXIT_FAILURE);
        }

        if (recvid < 0) {
            continue;
        }
        switch(msg.code) {
            case PULSE_STOP_THREAD:
                printf("Thread kill code received!\n");
                myInterruptDetach(interruptID);
                receivingRunning = false;
                break;

            case PULSE_INTRRUPT:
                uintptr_t gpioBase = mmap_device_io(GPIO_LENGTH, GPIO_BANK_0);
                out32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1), 0xffffffff);    //clear all interrupts.
                InterruptUnmask(INTR_GPIO_PORT0, interruptID);
                MsgSendPulse(connectionID_Encoder, -1, PULSE_GPIO,
                             in32(uintptr_t(gpioBase + GPIO_DATA_IN)));
                break;
        }
    }

    printf("Message thread stops...\n");
}
