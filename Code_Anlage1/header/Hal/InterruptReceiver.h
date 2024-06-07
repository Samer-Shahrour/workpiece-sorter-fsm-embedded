#pragma once

#define INTR_GPIO_PORT0 97
#define INTR_GPIO_PORT1 99

#define GPIO_LEVELDETECT0 0x140
#define GPIO_LEVELDETECT1 0x144

#define GPIO_RISINGDETECT 0x148
#define GPIO_FALLINGDETECT 0x14C

#define GPIO_IRQSTATUS_0 0x2C
#define GPIO_IRQSTATUS_1 0x30
#define GPIO_IRQSTATUS_SET_0 0x34
#define GPIO_IRQSTATUS_SET_1 0x38

void interruptThread(int channelID_Interrupt, int connectionID_Encoder);
void initInterrupt(int connectionID_ISR);

