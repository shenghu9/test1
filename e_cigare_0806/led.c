
#include "led.h"
#include "tenx_TM56F1522.h"
#include "gpio.h"

// -- a
// |    |
// f    b
//  -- g
// |    |
// e    c
//  -- d 

const unsigned char SEG[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

unsigned int mark_state;   //8位 代表显示屏8个LED状态

void LED_Init()
{
    //LED引脚初始化
    PxMOD_Config(GPIO_PA,0x70,GPIOx_CmosOutL);        // PA4\5\6 CMOS 推挽输出低
    PxMOD_Config(GPIO_PB,0x07,GPIOx_CmosOutL);        // PB[2:0] CMOS 推挽输出低

    //充电检测引脚
    PxMOD_Config(GPIO_PD,0x02,GPIOx_InputPD_WKUP);     //下拉带唤醒
}

void HW_Led_Scan(unsigned int ten,unsigned int one)
{
    unsigned int state;
    PxMOD_Config(GPIO_PA,0x70,GPIOx_InputHiz);        //高阻
    PxMOD_Config(GPIO_PB,0x07,GPIOx_InputHiz);

    switch (state)
    {
    case 0:
        PxMOD_Config(GPIO_PA,led1,GPIOx_CmosOutH);
        if((SEG[ten] & Bit_0)==Bit_0)    //A2
        {
            PxMOD_Config(GPIO_PA,led2,GPIOx_CmosOutL);
        }
        if((SEG[ten] & Bit_1)==Bit_1)    //B2
        {
            PxMOD_Config(GPIO_PA,led3,GPIOx_CmosOutL);
        }
        if((SEG[ten] & Bit_2)==Bit_2) 
        {
            PxMOD_Config(GPIO_PB,led4,GPIOx_CmosOutL);
        }
        if((SEG[ten] & Bit_3)==Bit_3) 
        {
            PxMOD_Config(GPIO_PB,led5,GPIOx_CmosOutL);
        }
        if((SEG[ten] & Bit_4)==Bit_4) 
        {
            PxMOD_Config(GPIO_PB,led6,GPIOx_CmosOutL);
        }
        state = 1;
        break;
    case 1:
        PxMOD_Config(GPIO_PA,led2,GPIOx_CmosOutH);
        if((SEG[ten] & Bit_5)==Bit_5)    //F2
        {
            PxMOD_Config(GPIO_PA,led1,GPIOx_CmosOutL);
        }
        if((SEG[ten] & Bit_6)==Bit_6)    //G2
        {
            PxMOD_Config(GPIO_PA,led3,GPIOx_CmosOutL);
        }
        if((SEG[one] & Bit_0)==Bit_0) 
        {
            PxMOD_Config(GPIO_PB,led4,GPIOx_CmosOutL);
        }
        if((SEG[one] & Bit_1)==Bit_1) 
        {
            PxMOD_Config(GPIO_PB,led5,GPIOx_CmosOutL);
        }
        if((SEG[one] & Bit_2)==Bit_2) 
        {
            PxMOD_Config(GPIO_PB,led6,GPIOx_CmosOutL);
        }
        state = 2;
        break;
    case 2:
        PxMOD_Config(GPIO_PA,led3,GPIOx_CmosOutH);
        if((SEG[one] & Bit_3)==Bit_3) 
        {
            PxMOD_Config(GPIO_PA,led1,GPIOx_CmosOutL);
        }
        if((SEG[one] & Bit_4)==Bit_4) 
        {
            PxMOD_Config(GPIO_PA,led2,GPIOx_CmosOutL);
        }
        if((SEG[one] & Bit_5)==Bit_5) 
        {
            PxMOD_Config(GPIO_PB,led4,GPIOx_CmosOutL);
        }
        if((SEG[one] & Bit_6)==Bit_6) 
        {
            PxMOD_Config(GPIO_PB,led5,GPIOx_CmosOutL);
        }
        if((mark_state & Bit_0)==Bit_0)     //K1
        {
            PxMOD_Config(GPIO_PB,led6,GPIOx_CmosOutL);
        }
        state = 3;
        break;
    case 3:
        PxMOD_Config(GPIO_PB,led4,GPIOx_CmosOutH);
        if((mark_state & Bit_1)==Bit_1) 
        {
            PxMOD_Config(GPIO_PA,led1,GPIOx_CmosOutL);
        }
        if((mark_state & Bit_2)==Bit_2) 
        {
            PxMOD_Config(GPIO_PA,led2,GPIOx_CmosOutL);
        }
        if((mark_state & Bit_3)==Bit_3) 
        {
            PxMOD_Config(GPIO_PA,led3,GPIOx_CmosOutL);
        }
        if((mark_state & Bit_4)==Bit_4) 
        {
            PxMOD_Config(GPIO_PB,led5,GPIOx_CmosOutL);
        }
        state = 4;
        break;
    case 4:
        PxMOD_Config(GPIO_PB,led5,GPIOx_CmosOutH);
        if((mark_state & Bit_5)==Bit_5) 
        {
            PxMOD_Config(GPIO_PA,led1,GPIOx_CmosOutL);
        }
        if((mark_state & Bit_6)==Bit_6) 
        {
            PxMOD_Config(GPIO_PA,led2,GPIOx_CmosOutL);
        }
        if((mark_state & Bit_7)==Bit_7) 
        {
            PxMOD_Config(GPIO_PA,led3,GPIOx_CmosOutL);
        }
        state = 0;
        break;
    default:
        state = 0;
        break;
    }
}


