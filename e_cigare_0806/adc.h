/**
******************************************************************************
* @file    adc.h
* @brief   adc Head File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2022/06/22
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/

#ifndef __ADC_H
#define __ADC_H

/*------------------------------------------------------------------------------------------------
  ADCTL[3]:ADST->ADC start bit
        0 >H/W clear after end of conversion
        1 >ADC start conversion   
 --------------------------------------------------------------------------------------------------*/
#define Adc_Start()  ADST = 1  

#define ADC_IO   PA2

/*------------------------------------------------------------------------------------------------
  ADCTL[2:0]:ADCKS->ADC clock frequency selection  
        000 >Fsys/256 
        001 >Fsys/128 
        010 >Fsys/64  
        011 >Fsys/32  
        100 >Fsys/16
        101 >Fsys/8
        110 >Fsys/4
        111 >Fsys/2                 
  -------------------------------------------------------------------------------------------------*/
typedef enum
{
  AdcClk_Div256 = 0,
  AdcClk_Div128 = 1,
  AdcClk_Div64  = 2,
  AdcClk_Div32  = 3,  
  AdcClk_Div16  = 4,
  AdcClk_Div8   = 5,
  AdcClk_Div4   = 6,
  AdcClk_Div2   = 7
}AdcClk_TypeDef;

/*--------------------------------------------------------------------------------------
  ADCTL2[7:6]:ADVREFS->ADC reference voltage select
         0 0 >VCC 
         0 1 >2.5207V 
         1 0 >3.0379V
         1 1 >4.0646V
 --------------------------------------------------------------------------------------------------*/
typedef enum
{
  AdcVref_VCC     = 0,
  AdcVref_2P5207V = 1,
  AdcVref_3P0379V = 2,
  AdcVref_4P0646V = 3  
}AdcVref_TypeDef;


/*--------------------------------------------------------------------------------------
  ADCTL2[4:0]: ADCHS->ADC channel select
        00000> ADC0 (PA0) 
        00001> ADC1 (PA1) 
        00010> ADC2 (PA2) 
        00011> ADC3 (PA3) 
        00100> ADC4 (PA4) 
        00101> ADC5 (PA5) 
        00110> ADC6 (PA6) 
        00111> ADC7 (PB0) 
        01000> ADC8 (PB1) 
        01001> ADC9 (PB2) 
        01010> ADC10(PB4)
        01011> ADC11(PB5)
        01100> ADC12(PB6)
        01101> ADC13(PB7)
        01110> VBGO (PA3)
        01111> OPO  (PA3)
        10111> 1/4 VCC
       others> Reserved
 --------------------------------------------------------------------------------------------------*/
typedef enum
{
  AdcChanel_PA0   = 0,
  AdcChanel_PA1   = 1,
  AdcChanel_PA2   = 2,
  AdcChanel_PA3   = 3,
  AdcChanel_PA4   = 4,
  AdcChanel_PA5   = 5,
  AdcChanel_PA6   = 6,
  AdcChanel_PB0   = 7,
  AdcChanel_PB1   = 8,
  AdcChanel_PB2   = 9,
  AdcChanel_PB4   =10,
  AdcChanel_PB5   =11,
  AdcChanel_PB6   =12,
  AdcChanel_PB7   =13,
  AdcChanel_VBGO  =14,
  AdcChanel_OPO   =15,
  AdcChanel_1_4VCC=23  
}AdcChanel_TypeDef; 
             
        
void Adc_Init(AdcClk_TypeDef clk,AdcVref_TypeDef vref,AdcChanel_TypeDef chl);
unsigned int Adc_Get_Value(void);
unsigned int Adc_Get_Average(void);

#endif
