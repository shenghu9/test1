/**
******************************************************************************
* @file    wdt.c
* @brief   wdt Source File.
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
#include "wktwdt.h" 

/*------------------------------------------------------------------------------              
  sfr OPTION:STATUS INT0 INT1 WDT WKT related @81H:
      OPTION[3:2]:WDTPSC->WDT Period @5V
             0 0: 102ms
             0 1: 205ms
             1 0: 819ms
             1 1: 1638ms                                                                        
  ------------------------------------------------------------------------------*/
void Wdt_Init(WKTWdtPsc_TypeDef wdtpsc)
{
  //OPTIONbits.WKTPSC= 
  OPTIONbits.WDTPSC=wdtpsc; 
 
}
