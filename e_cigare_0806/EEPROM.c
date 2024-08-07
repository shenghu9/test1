/**
******************************************************************************
* @file    EEPROM.c
* @brief   EEPROM Source File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2022/08/25
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/

#include "tenx_TM56F1522.h"
#include "gpio.h" 
#include "EEPROM.h" 

bit Timeout_f=0;

/*----------------------------------------------------------------------------
  sfr EEPCTL:EEPROM related @190H:
   
      EEPCTL[7]:EEPTO   -> EEPROM Write Time-Out flag
                           0:EEPROM Write no Time-Out
                           1:EEPROM Write is Time-Out
                           
      EEPCTL[1:0]:EEPTE -> EEPROM Write Time-Out Enable. 
                           00: Disable
                           01: 0.9ms
                           10: 3.6ms
                           11: 7.2ms                        
 ----------------------------------------------------------
  sfr EEPEN:EEPROM related @191H:
            EEPROM Access Enable
            Write 0xE2 to this register will enable EEPROM access
            Write others value to this register will disable EEPROM access                            
  ----------------------------------------------------------------------------*/  

/*----------------------------------------------------------
  EEPROM write one byte
  ----------------------------------------------------------*/
bit EEPROM_WriteByte(unsigned char val,unsigned int addr)
{ 
	EEPROM_En(Enable);
	
	DPH=(addr>>8)&0xFF;
	DPL=(addr>>0)&0xFF;
	
	EEPROM_Timout_En(EEPTO_7p2ms);
 
	LVRPD=0x37;                    // Force LVR and POR Disable
	
	EEPDT=val;

	Timeout_f=EEPCTLbits.EEPTO;          // Read time-out state 

	EEPROM_En(Disable);
	LVRPD=0x00;                    // Force LVR and POR Enable
	//
	return Timeout_f;
}

/*----------------------------------------------------------
  EEPROM read one byte
  ----------------------------------------------------------*/
unsigned char EEPROM_ReadByte(unsigned int addr)
{
	unsigned char buf;
	
	EEPROM_En(Enable);
	
	DPH=(addr>>8)&0xFF;
	DPL=(addr>>0)&0xFF;
	
	TABR=0x01;
	buf =TABR;
	
	EEPROM_En(Disable);
	
	return buf;
}

/*----------------------------------------------------------
  EEPROM write mult bytes
  ----------------------------------------------------------*/
bit EEPROM_WriteMultByte(unsigned char val,unsigned int addr,unsigned char leng)
{
	unsigned char i;
  
	for(i=0;i<leng;i++)
	{
	  if(EEPROM_WriteByte(val,addr+i)==EEPROM_Timerout) return 0; 
	}
	
	return 1;
}

/*----------------------------------------------------------
  EEPROM read mult bytes
  ----------------------------------------------------------*/

bit EEPROM_ReadMultByte(unsigned char val,unsigned int addr,unsigned char leng)
{
	unsigned char i;
	
	for(i=0;i<leng;i++)
	{
		if(EEPROM_ReadByte(addr+i)!=val) return 0;
	}
	
	return 1;
}  