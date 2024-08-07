/**
******************************************************************************
* @file    INTx.h
* @brief   INTx Head File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2022/06/22
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/

#ifndef __INTX_H
#define __INTX_H

/*------------------------------------------------------------------------------------------------
   OPTION[6]:INT0EDG->INT1 pin edge interrupt event
   OPTION[5]:INT1EDG->INT1 pin edge interrupt event
          0 >falling edge to trigger
          1 >rising  edge to trigger 
 --------------------------------------------------------------------------------------------------*/
typedef enum
{
  INTxEDG_Falling=0,
	INTxEDG_Rising =1
}INTxEDG_TypeDef;

/*------------------------------------------------------------------------------------------------
  OPTION2[2]:INT2 pin select
          0 >PA7
          1 >PB5
  
  OPTION2[1]:INT1 pin select
          0 >PA1
          1 >PB1
          
  OPTION2[0]:INT0 pin select
          0 >PA3
          1 >PB2                 
  -------------------------------------------------------------------------------------------------*/
typedef enum
{
  INTxPin_PA = 0,
  INTxPin_PB = 1
}INTxPin_TypeDef;

#define ExINT0  0x01
#define ExINT1  0x02
#define ExINT2  0x04

/*--------------------------------------------------------------------------------------
  sfr INTIE:Interrupt Enable related @0BH:
            INTIE[2]: INT2IE->INT2 pin (PA7 or PB5) Interrupt enable 
            INTIE[1]: INT1IE->INT1 pin (PA1 or PB1) Interrupt enable
            INTIE[0]: INT0IE->INT0 pin (PA3 or PB2) Interrupt enable 
                  0 > INTx Disable  (x=0,1,2)
                  1 > INTx Enable   (x=0,1,2)  
  
  sfr INTIF:Interrupt Flag   related @0CH:  
            INTIF[2]: INT2IF->INT2 pin (PA7 or PB5) Interrupt Flag
                      write 0: clear this flag; 
                      write 1: no action 
                      set by H/W at INT2 pin¡¯s falling edge  
             
            INTIF[1]:INT1IF->INT1 pin (PA1 or PB1) Interrupt Flag
            INTIF[0]:INT0IF->INT0 pin (PA3 or PB2) Interrupt Flag 
                     write 0: clear this flag; 
                     write 1: no action   
                     set by H/W at INTx pin¡¯s falling/rising edge (x=0,1)
 --------------------------------------------------------------------------------------------------*/
#define INT0IE_En(x)               \
        {                          \
          INT0IF=0;                \
          INT0IE=x;                \
        }
        
#define INT1IE_En(x)               \
        {                          \
          INT1IF=0;                \
          INT1IE=x;                \
        }
        
#define INT2IE_En(x)               \
        {                          \
          INT2IF=0;                \
          INT2IE=x;                \
        }                
        
void INTx_Init(unsigned char INTx,INTxPin_TypeDef pin,INTxEDG_TypeDef edg);

#endif
