/**
******************************************************************************
* @file    wktwdt.h
* @brief   wktwdt Head File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2022/06/22
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/

#ifndef __wktwdt_H
#define __wktwdt_H

#include "tenx_TM56F1522.h"

/*------------------------------------------------------------------------------------------------
  STATUS[4]:TO->WDT Time Out Flag,Read only        
 --------------------------------------------------------------------------------------------------*/
#define GetWdtTimeOutFlag()  return(TO) 
#define WDTClr()	           asm("CLRWDT") 

/*------------------------------------------------------------------------------------------------
  sfr LVCTL:LVD/LVR related @16H:
      
      LVCTL[7  ]:LVDF  ->Low voltage detection flag,Read only
                         0: VCC > VLVD
                         1: VCC < VLVD
      LVCTL[6  ]:LVDHYS->LVD Hystertsis, 25mV@LVD=2.19V, 70mV@LVD=4.15V (tt)
                         0: disable
                         1: enable
  
      LVCTL[5  ]:LVRSAV->POR/LVR auto power off in STOP/IDLE mode
                         0: POR/LVR enable
                         1: POR/LVR enable in Slow/Fast mode, disable in STOP/IDLE mode
                           (PORPD=1, POR force disable. 
                            LVRPD=1, LVR force disable)
                        
      LVCTL[4  ]:LVDSAV->LVD auto power off in STOP/IDLE mode
                         0: LVD enable
                         1: LVD enable in Slow/Fast mode,disable in STOP/IDLE mode 
                                           
      LVCTL[3:0]:LVDS  ->LVD voltage (VLVD) select (TBD)
                         0000:Disable
                         0001:2.19V 
                         0100:2.61V 
                         1000:3.17V 
                         1100:3.73V
                         1111:4.15V(TBD)        
 --------------------------------------------------------------------------------------------------*/
#define GetLVDF()     return(LVDF) 
#define LVDHYS_En(x)  LVDHYS=x
#define LVRSAV_En(x)  LVRSAV=x
#define LVDSAV_En(x)  LVDSAV=x 

#define LVDS_Disable  0
#define LVDS_2V19     1
#define LVDS_2V33     2
#define LVDS_2V47     3
#define LVDS_2V61     4
#define LVDS_2V75     5
#define LVDS_2V89     6
#define LVDS_3V03     7
#define LVDS_3V17     8
#define LVDS_3V31     9
#define LVDS_3V45     10
#define LVDS_3V59     11
#define LVDS_3V73     12
#define LVDS_3V87     13
#define LVDS_4V01     14
#define LVDS_4V15     15

/*------------------------------------------------------------------------------------------------
  sfr OPTION:STATUS INT0 INT1 WDT WKT related @81H:
      OPTION[3:2]:WDTPSC->WDT Period @5V
             0 0: 102ms
             0 1: 205ms
             1 0: 819ms
             1 1: 1638ms                       
                         
      OPTION[1:0]:WKTPSC->WKT Period @3V
             0 0: 13ms
             0 1: 26ms
             1 0: 51ms
             1 1: 102ms              
  -------------------------------------------------------------------------------------------------*/
typedef enum
{
  WKTWdtPsc_Div1 = 0,
  WKTWdtPsc_Div2 = 1,
  WKTWdtPsc_Div4 = 2,
  WKTWdtPsc_Div8 = 3
}WKTWdtPsc_TypeDef;

/*----------------------------------------------------------------------------------
  sfr LVRPD:LVR POR related @109H:
   
   Write:
         Write 37h to force LVR+POR Disable
         Write 38h to force LVR Disable, POR still enable
         Write 39h to force POR Disable, LVR still enable
         Write others LVR and POR enable   
  
   Read:   
      LVRPD[1]:PORPDF -> POR force power down flag
                         0: Disable(POR enable)
                         1: Enable (POR is forced power down)
                           
      LVRPD[0]:LVRPDF-> LVR force power down flag
                         0: Disable(LVR enable)
                         1: Enable (LVR is forced power down)               
  --------------------------------------------------------------------------------*/
#define LVRDIS_PORDis()   LVRPD=0x37
#define LVRDIS_POREN()    LVRPD=0x38  
#define PORDis_LVREN()    LVRPD=0x39
#define LVREN_POREN()     LVRPD=0x00

#define Get_PORPD_FLAG() return(PORPD)
#define Get_LVRPD_FLAG() return(LVRPD0)             
        
void WKT_Init(WKTWdtPsc_TypeDef psc);
void Wdt_Init(WKTWdtPsc_TypeDef wdtpsc);

#endif
