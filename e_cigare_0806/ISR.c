/**
******************************************************************************
* @file    ISR.c
* @brief   ISR Source File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2022/06/22
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/


#include "tenx_TM56F1522.h"
#include "ISR.h"

/*----------------------------------------------------------------------
  sfr INTIE:Interrupt related @0BH:
      INTIE[7]:ADCIE ->ADC    Interrupt Enable
      INTIE[6]:T2IE  ->TImer2 Interrupt Enable
      INTIE[5]:TM1IE- >TImer1 Interrupt Enable
      INTIE[4]:TM0IE ->TImer0 Interrupt Enable                  
      INTIE[3]:WKTIE -> Wakeup Timer interrupt enable 
	                    and Wakeup Timer enable
      INTIE[2]:INT2IE->XINT2  Interrupt Enable, PA7 or PB5    
      INTIE[1]:INT1IE->XINT1  Interrupt Enable, PA1 or PB1    
      INTIE[0]:INT0IE->XINT0  Interrupt Enable, PA3 or PB2
					   
  sfr INTIE1:Interrupt related @0DH:      
      INTIE1[4]:CMPIE->Comparator Interrupt enable            
      INTIE1[2]:TKIE ->Touch Key  Interrupt Enable    
      INTIE1[1]:PWMIE->PWM0       Interrupt Enable    
      INTIE1[0]:LVDIE->LVD        Interrupt Enable	  
                       0: Disable
                       1: Enable 					   
  ------------------------------------------------------------------------------------
   sfr INTIF:Interrupt related @0CH:
      INTIF[7]:ADCIF ->ADC Interrupt event pending Flag
	                   set by H/W after ADC end of conversion
      INTIF[6]:T2IF  ->TImer2 Interrupt event pending Flag
	                   set by H/W while T2 overflows
      INTIF[5]:TM1IF- >TImer1 Interrupt event pending Flag
	                   set by H/W while Timer1 overflows
      INTIF[4]:TM0IF ->TImer0 Interrupt event pending Flag
                       set by H/W while Timer0 overflows	  
      INTIF[3]:WKTIF ->WKT Interrupt event pending Flag
	                   set by H/W while Wakeup Timer is timeout 
      INTIF[2]:INT2IF->XINT2  Interrupt event pending Flag, PA7 or PB5    
                       set by H/W at INT2 pin’s falling edge  
	  INTIF[1]:INT1IF->XINT1  Interrupt event pending Flag, PA1 or PB1    
                       set by H/W at INT1 pin’s falling or rising edge
	  INTIF[0]:INT0IF->XINT0  Interrupt event pending Flag, PA3 or PB2
					   set by H/W at INT0 pin’s falling or rising edge
 
   sfr INTIF1:Interrupt related @0EH:      
      INTIF1[4]:CMPIF->Comparator Interrupt event pending Flag
                       set by H/W while CMPO match trigger condition	  
      INTIF1[2]:TKIF ->Touch Key  Interrupt event pending Flag
                       set by H/W after touch key end of conversion					   
      INTIF1[1]:PWMIF->PWM0 Interrupt event pending Flag
                       set by H/W after PWM period counter roll over	  
      INTIF1[0]:LVDIF->LVD Interrupt event pending Flag
                       set by H/W after VCC < VLVD	  
                       0: Interrupt no 	
                       1: Interrupt,set by H/W,clear by write 0
 ----------------------------------------------------------------------*/
void Interrupt_EnConfig(IntSrc_TypeDef IntSrc)
{  
  unsigned char tmp=0;
  
  if(IntSrc<0x0100) 
  { 
    tmp=(unsigned char)IntSrc;
	
    INTIF &=~tmp;	
	  INTIE |= tmp;
  }
  else
  {
	  tmp=((unsigned char)(IntSrc>>8))&0x17; 
	 
	  INTIF1 &=~tmp;
	  INTIE1 |= tmp;
	}   
}

void Interrupt_DisConfig(IntSrc_TypeDef IntSrc)
{  
  unsigned char tmp=0;
  
  if(IntSrc<0x0100) 
  { 
    tmp=(unsigned char)IntSrc;
	
    INTIF &=~tmp;
	  INTIE &=~tmp;
  }
  else
  {
	  tmp=((unsigned char)(IntSrc>>8))&0x17; 
	 
	  INTIF1 &=~tmp;	
	  INTIE1 &=~tmp;
  }   
}