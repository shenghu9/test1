/**
******************************************************************************
* @file    EEPROM.h
* @brief   EEPROM Head File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2022/08/25
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/

#ifndef __EEPROM_H
#define __EEPROM_H

#include "Sys_Bsp.h"

/*------------------------------------------------------------------------------------------------
  sfr EEPCTL:EEPROM related @190H:
   
      EEPCTL[7]:EEPTO   -> EEPROM Write Time-Out flag
                           0:EEPROM Write no Time-Out
                           1:EEPROM Write is Time-Out
                           
      EEPCTL[1:0]:EEPTE -> EEPROM Write Time-Out Enable. 
                           00: Disable
                           01: 0.9ms
                           10: 3.6ms
                           11: 7.2ms 
  ------------------------------------------------------------------------------------*/
#define EEPROM_Timerout  1

#define EEPTO_None       0
#define EEPTO_0p9ms      1
#define EEPTO_3p6ms      2
#define EEPTO_7p2ms      3

#define EEPROM_Timout_En(x)  EEPCTLbits.EEPTE=x

/*------------------------------------------------------------------------------------------------
  sfr EEPEN:EEPROM related @191H:
            EEPROM Access Enable
            Write 0xE2 to this register will enable EEPROM access
            Write others value to this register will disable EEPROM access                     
                
  -------------------------------------------------------------------------------------------------*/
#define EEPROM_En(x)                   \
        {                              \
          if(x==Enable) EEPEN=0xE2; \
          else          EEPEN=0;    \
        }
        

bit EEPROM_WriteByte(unsigned char val,unsigned int addr);
bit EEPROM_WriteMultByte(unsigned char val,unsigned int addr,unsigned char leng);        
bit EEPROM_ReadMultByte(unsigned char val,unsigned int addr,unsigned char leng);
unsigned char EEPROM_ReadByte(unsigned int addr);

#endif
