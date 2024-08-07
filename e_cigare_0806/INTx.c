/**
******************************************************************************
* @file    Timer.c
* @brief   Timer Source File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2022/01/12
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/

#include "tenx_TM56F1522.h"
#include "gpio.h" 
#include "INTx.h" 

/*----------------------------------------------------------
  OPTION[6]:INT0EDG->INT1 pin edge interrupt event
  OPTION[5]:INT1EDG->INT1 pin edge interrupt event
         0 >falling edge to trigger
         1 >rising  edge to trigger
 		
  OPTION2[2]:INT2 pin select
          0 >PA7
          1 >PB5
  
  OPTION2[1]:INT1 pin select
          0 >PA1
          1 >PB1
          
  OPTION2[0]:INT0 pin select
          0 >PA3
          1 >PB2 
 ----------------------------------------------------------*/
void INTx_Init(unsigned char INTx,INTxPin_TypeDef pin,INTxEDG_TypeDef edg)
{
  if((INTx&ExINT0)==ExINT0)
  {
    if(pin==INTxPin_PA)
    {
      if(edg==INTxEDG_Falling)
      {
        PxMOD_Config(GPIO_PA,Bit_3,GPIOx_InputPU_WKUP);
      }
      else // if(edg==INTxEDG_Rising)
      {
        PxMOD_Config(GPIO_PA,Bit_3,GPIOx_InputPD_WKUP);
      }
    }
    else // if(pin==INTxPin_PB)
    {
      if(edg==INTxEDG_Falling)
      {
        PxMOD_Config(GPIO_PB,Bit_2,GPIOx_InputPU_WKUP);
      }
      else // if(edg==INTxEDG_Rising)
      {
        PxMOD_Config(GPIO_PB,Bit_2,GPIOx_InputPD_WKUP);
      }
    }
    OPTIONbits.INT0EDG=edg;
    INT0SEL=pin;
  } // end ExINT0 
  
  if((INTx&ExINT1)==ExINT1)
  {
    if(pin==INTxPin_PA)
    {
      if(edg==INTxEDG_Falling)
      {
        PxMOD_Config(GPIO_PA,Bit_1,GPIOx_InputPU_WKUP);
      }
      else // if(edg==INTxEDG_Rising)
      {
        PxMOD_Config(GPIO_PA,Bit_1,GPIOx_InputPD_WKUP);
      }
    }
    else // if(pin==INTxPin_PB)
    {
      if(edg==INTxEDG_Falling)
      {
        PxMOD_Config(GPIO_PB,Bit_1,GPIOx_InputPU_WKUP);
      }
      else // if(edg==INTxEDG_Rising)
      {
        PxMOD_Config(GPIO_PB,Bit_1,GPIOx_InputPD_WKUP);
      }
    }
    INT1EDG=edg;
    INT1SEL=pin;
  } // end ExINT1
  
  if((INTx&ExINT2)==ExINT2)
  {
    if(pin==INTxPin_PA)
    {
      PxMOD_Config(GPIO_PA,Bit_7,GPIOx_InputPU_WKUP);      
    }
    else // if(pin==INTxPin_PB)
    {
      PxMOD_Config(GPIO_PB,Bit_5,GPIOx_InputPU_WKUP);
    }
    INT2SEL=pin;
  } // end ExINT2
}