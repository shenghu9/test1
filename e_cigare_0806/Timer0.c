
#include "tenx_TM56F1522.h"
#include "tenx_TM56F1522_sfr.h"
#include "gpio.h" 
#include "Timerx.h" 

/*---------------------------------------------------------- 		
  sfr TM0CTL:Timer0 related @11H:  
      TM0CTL[6]:TM0STP->Stop Timer0      
                        0: Timerx runs  (x=0,1)
                        1: Timerx stops (x=0,1)
                        
      TM0CTL[5]:TM0EDG->TM0CKI (PA2) edge
                        0: rising edge
                        1: falling edge
                        
      TM0CTL[4]:TM0CKS->Timer0 prescaler clock source
                        0: Fsys/2
                        1: TM0CKI (PA2)
                        
      TM0CTL[3:0]:TM0PSC->Timer0 prescaler.Timer0 prescaler clock source divided by
                          0000  Div1
                          0001  Div2
                          0010  Div4             
                          0011  Div8
                          0100  Div16
                          0101  Div32
                          0110  Div64
                          0111  Div128
                          1xxx  Div256  
 ----------------------------------------------------------*/
void Timer0_Init(TM0_ClkSrc_TypeDef clksrc,TM01_ClkPsc_TypeDef clkpsc,unsigned char rld)
{
	switch(clksrc)
  {		
		case TM0_FsysDiv2:
			   TM0CKS=0;
         TM0CTLbits.TM0PSC=clkpsc;				   
		     break;
           			     
		case TM0_CKI_Rising:
		     PxMOD_Config(GPIO_PA,Bit_2,GPIOx_InputPD);
		     TM0EDG=0;
				 TM0CKS=1;
		     break;
			     
		case TM0_CKI_Falling:
		default:
		     PxMOD_Config(GPIO_PA,Bit_2,GPIOx_InputPU);
			   TM0EDG=1;
         TM0CKS=1;
			   break;			     
		}    
    TM0RLD=rld;
    TM0   =rld;			
}
