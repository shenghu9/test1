/**
******************************************************************************
* @file    Timerx.h
* @brief   Timerx Head File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2022/06/22
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/

#ifndef __TIMERX_H
#define __TIMERX_H

/*--------------------------------------------------------------------------------------
  sfr TM0CTL:Timer0 related @11H:
  sfr TM1CTL:Timer1 related @14H:
  sfr T2CTL :Timer2 related @15H:
  
  TM0CTL[6]:TM0STP 
  TM1CTL[6]:TM1STP
  T2CTL [4]:T2CLR 
            0->Timerx Enablec,Release,runs  (x=0,1,2)
            1->Timerx Disable,Stop          (x=0,1,2)
 --------------------------------------------------------------------------------------------------*/
#define TM0Cnt_En(x)               \
        {                          \
          if(x==Enable) TM0STP=0;  \
          else          TM0STP=1;  \
        }
        
#define TM1Cnt_En(x)               \
        {                          \
          if(x==Enable) TM1STP=0;  \
          else          TM1STP=1;  \
        }
        
#define TM2Cnt_En(x)               \
        {                          \
          if(x==Enable) T2CLR=0;   \
          else          T2CLR=1;   \
        }                
        
/*------------------------------------------------------------------------------------------------
   TM0CTL[5]:TM0EDG->TM0CKI (PA2) edge
                     0: rising edge
                     1: falling edge
                        
   TM0CTL[4]:TM0CKS->Timer0 prescaler clock source
                     0: Fsys/2
                     1: TM0CKI (PA2)
  -----------------------------------------------------------------                      
  ClkSrc:TM0CTL[5]  TM0CTL[4]
         TM0EDG     TM0CKS
            0          0      ->Fsys/2
            0          1      ->TM0CKI rising  edge
            1          1      ->TM0CKI falling edge
 --------------------------------------------------------------------------------------------------*/
typedef enum
{
  TM0_FsysDiv2   =0,
	TM0_CKI_Rising =1,
  TM0_CKI_Falling=3 
}TM0_ClkSrc_TypeDef;

/*------------------------------------------------------------------------------------------------
  TM0CTL[3:0]:TM0PSC->Timer0 prescaler.Timer0 prescaler clock source divided by
  TM1CTL[3:0]:TM1PSC->Timer1 prescaler.Timer1 prescaler clock source divided by
                      0000  Div1
                      0001  Div2
                      0010  Div4             
                      0011  Div8
                      0100  Div16
                      0101  Div32
                      0110  Div64
                      0111  Div128
                      1xxx  Div256
  -------------------------------------------------------------------------------------------------*/
typedef enum
{
  TM01_ClkPsc_1   = 0x00,
  TM01_ClkPsc_2   = 0x01,
  TM01_ClkPsc_4   = 0x02,
  TM01_ClkPsc_8   = 0x03,
  TM01_ClkPsc_16  = 0x04,
  TM01_ClkPsc_32  = 0x05,
  TM01_ClkPsc_64  = 0x06,
  TM01_ClkPsc_128 = 0x07,
  TM01_ClkPsc_256 = 0x08
}TM01_ClkPsc_TypeDef;

/*------------------------------------------------------------------------------------------------
  CLKCTL[4] :SLOWSTP->Stop Slow-clock after execute SLEEP instruction
         0  >Slow-clock keeps running after execute SLEEP instruction
         1  >Slow-clock stops running after execute SLEEP instruction
 
  T2CTL[3:2]: T2CKS->T2 clock source selection
        0 0 > Slow-clock
        0 1 > Fsys/128
        1 x > FIRC/512 (16 MHz/512)
 --------------------------------------------------------------------------------------------------*/
typedef enum
{
  TM2_SCK        =0,
	TM2_FsysDiv128 =1,
  TM2_FIRCDiv512 =2 
}TM2_ClkSrc_TypeDef;

/*------------------------------------------------------------------------------------------------
  T2CTL[1:0]: T2PSC->T2 clock source prescaler
        0 0 > 32768
        0 1 > 16384
        1 0 > 8192
        1 1 > 128
 --------------------------------------------------------------------------------------------------*/
typedef enum
{
  TM2_ClkPsc_32768  =0,
	TM2_ClkPsc_16384  =1,
  TM2_ClkPsc_8192   =2,
  TM2_ClkPsc_128    =3 
}TM2_ClkPsc_TypeDef;
     
void Timer0_Init(TM0_ClkSrc_TypeDef clksrc,TM01_ClkPsc_TypeDef clkpsc,unsigned char rld);
void Timer1_Init(TM01_ClkPsc_TypeDef clkpsc,unsigned char rld);
void Timer2_Init(TM2_ClkSrc_TypeDef clksrc,TM2_ClkPsc_TypeDef clkpsc);
#endif
