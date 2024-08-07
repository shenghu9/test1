/*
**************************************************************************************************
* @file    Sys_Bsp.h
* @brief   Sys_Bsp Head File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2022/06/22
*
* Copyright (C) Hitenx (ShenZhen) Technology Co., Ltd
**************************************************************************************************
*/
#ifndef _Sys_Bsp_H__
#define _Sys_Bsp_H__

#define Enable    1
#define Disable   0

/*------------------------------------------------------------------
  The device is operated in one of four modes: 
                      FAST mode
                      SLOW mode
                      IDLE mode
                      STOP mode.

  SIRC:90KHz  (default)
  FIRC:16MHz   Adjusted by IRCF(10FH)
               IRCF=00H->frequency is the lowest
               IRCF=7FH->frequency is the highest
  SXT:
  FXT: 
  
  IDLE Mode: 
           SIRC or SXT running by:  
           Set SLOWSTP=0 (provide T2 block running in IDLE mode) or
           Set WKTIE=1 or WDTE=11 (keep WKT/WDT operating in IDLE mode)
       
  STOP Mode:
           All clocks stopped by:
           SLOWSTP=1
           WKTIE  =0
           WDTE   =0x or 10  
           
                   
  ------------------------------------------------------------------*/
typedef enum
{
  SCK_SRC  =0,   // 80KHz
  SCK_SXT  =1    // 32.768KHz
}SCK_TypeDef;

typedef enum
{
  FCK_FRC  =0,   // 16.588 MHz
  FCK_FXT  =1    // 1~16MHz
}FCK_TypeDef;

typedef enum
{
  SysClk_SCK =0,  // ÂýÖÓ
  SysClk_FCK =1   // ¿ìÖÓ
}SysClk_TypeDef;

typedef enum
{
  SysClkPsc_Div8=0,
  SysClkPsc_Div4=1,
  SysClkPsc_Div2=2,
  SysClkPsc_Div1=3
}SysClkPsc_TypeDef;

/*--------------------------------------------------------------------------------------
  CLKCTL[4] :SLOWSTP->Stop Slow-clock after execute SLEEP instruction
         0  >Slow-clock keeps running after execute SLEEP instruction
         1  >Slow-clock stops running after execute SLEEP instruction

 --------------------------------------------------------------------------------------------------*/
#define SLOWSTP_En(x)               \
        {                           \
          if(x==Enable) SLOWSTP=1;  \
          else          SLOWSTP=0;  \
        }

void Bsp_SysClock_Config(SCK_TypeDef SlowClk,FCK_TypeDef FastClk,SysClk_TypeDef SysClk,SysClkPsc_TypeDef SysClkPsc);
/**************************************************************************************************/
#endif
