
#ifndef __LED_H
#define __LED_H

#include "tenx_TM56F1522.h"


enum EVENT_TYPE
{
    EVENT_TIME0 = 0X01,
    EVENT_CHARGE = 0x02,
    EVENT_20ms = 0x04,
    EVENT_Smoke = 0x08,
    EVENT_Power_Off = 0x10,
};

extern unsigned int event;

#define event_set(x) (event |= x)
#define event_clr(x) (event &= ~x)


#define  led1  0x10
#define  led2  0x20
#define  led3  0x40
#define  led4  0x01
#define  led5  0x02
#define  led6  0x04

#define LED1_IO  PA4
#define LED2_IO  PA5
#define LED3_IO  PA6
#define LED4_IO  PB0
#define LED5_IO  PB1
#define LED6_IO  PB2

void LED_Init();
void HW_Led_Scan(unsigned int ten,unsigned int one);

#endif
