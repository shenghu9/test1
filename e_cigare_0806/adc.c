
#include "tenx_TM56F1522.h"
#include "gpio.h" 
#include "adc.h" 

unsigned int  adc_temp;

/*------------------------------------------------------------------------------              
  ADCTL[7:4]:ADCDL->ADC output data bit 3~0
  

  ADCTL[3]  :ADST->ADC start bit
        0   >H/W clear after end of conversion
        1   >ADC start conversion
 		
  ADCTL[2:0]:ADCKS->ADC clock frequency selection  
        000 >Fsys/256 
        001 >Fsys/128 
        010 >Fsys/64  
        011 >Fsys/32  
        100 >Fsys/16
        101 >Fsys/8
        110 >Fsys/4
        111 >Fsys/2
  
  ADCTL2[7:6]:ADVREFS->ADC reference voltage select
         0 0 >VCC 
         0 1 >2.5207V 
         1 0 >3.0379V
         1 1 >4.0646V
  
  ADCTL2[4:0]:ADCHS->ADC channel select
        00000> ADC0 (PA0) 
        00001> ADC1 (PA1) 
        00010> ADC2 (PA2) 
        00011> ADC3 (PA3) 
        00100> ADC4 (PA4) 
        00101> ADC5 (PA5) 
        00110> ADC6 (PA6) 
        00111> ADC7 (PB0) 
        01000> ADC8 (PB1) 
        01001> ADC9 (PB2) 
        01010> ADC10(PB4)
        01011> ADC11(PB5)
        01100> ADC12(PB6)
        01101> ADC13(PB7)
        01110> VBGO (PA3)
        01111> OPO  (PA3)
        10111> 1/4 VCC
       others> Reserved                                                                         
  ------------------------------------------------------------------------------*/
void Adc_Init(AdcClk_TypeDef clk,AdcVref_TypeDef vref,AdcChanel_TypeDef chl)
{
  ADCTLbits.ADCKS   =clk;
  ADCTL2bits.ADVREFS=vref; 

  if(chl==AdcChanel_PA0)       PAMOD10bits.PA0MOD=3;
  else if(chl==AdcChanel_PA1)  PAMOD10bits.PA1MOD=3;
  
  else if(chl==AdcChanel_PA2)  PAMOD32bits.PA2MOD=3;
  else if(chl==AdcChanel_PA3)  PAMOD32bits.PA3MOD=3;
  
  else if(chl==AdcChanel_PA4)  PAMOD54bits.PA4MOD=3;
  else if(chl==AdcChanel_PA5)  PAMOD54bits.PA5MOD=3;
  
  else if(chl==AdcChanel_PA6)  PAMOD76bits.PA6MOD=3;
  
  else if(chl==AdcChanel_PB0)  PBMOD10bits.PB0MOD=3;
  else if(chl==AdcChanel_PB1)  PBMOD10bits.PB1MOD=3;
  
  else if(chl==AdcChanel_PB2)  PBMOD32bits.PB2MOD=3;
  
  else if(chl==AdcChanel_PB4)  PBMOD54bits.PB4MOD=3;
  else if(chl==AdcChanel_PB5)  PBMOD54bits.PB5MOD=3;
  
  else if(chl==AdcChanel_PB6)  PBMOD76bits.PB6MOD=3;
  else if(chl==AdcChanel_PB7)  PBMOD76bits.PB7MOD=3;
  
  else if(chl==AdcChanel_VBGO) 
  {
    PAMOD32bits.PA3MOD=3;
    LVRPD=0x39;            // POR disable ,LVR enable
    LVCTLbits.LVRSAV  =1;
  }  
  else if(chl==AdcChanel_OPO)  
  {
    PAMOD32bits.PA3MOD=3;
    
    
  }
  ADCTL2bits.ADCHS =chl;
}

/*--------------------------------------------------------------------------------
  A total of 50 ADC clock cycles are required to perform the complete conversion
  --------------------------------------------------------------------------------*/
unsigned int Adc_Get_Value(void)  
{                   
    ADST = 1;                   // ADC Start      
    while(ADST);                // wait ADC finish

	  adc_temp  =((unsigned int)ADCDH) << 4;  
    adc_temp |= ADCTL>>4;	  
	
    return adc_temp ;	
}

unsigned int Adc_Get_Average(void)
{
  unsigned char k            = 0;
	unsigned int adc_value_max = 0;
	unsigned int adc_value_min = 0;
	unsigned int adc_sum       = 0;
	unsigned int adc_current   = 0;	
 	
	GPR1=1;
	while(1)
	{
	  adc_current = Adc_Get_Value();
	  if(adc_current>0 && adc_current<4095)
	  {
	    if(GPR1)
	    {
	      GPR1=0;
	      adc_value_max = adc_current;
	      adc_value_min = adc_current;
	    }
	    else
	    {
	      if(adc_current > adc_value_max)
		    {
			    adc_value_max = adc_current;
		    }
		    else if(adc_current < adc_value_min)
		    {
			    adc_value_min = adc_current;
		    }		        
	    }
	    adc_sum += adc_current;	
	    k++;
	    if(k>9) break;
	  }
	}	

	adc_sum = adc_sum - adc_value_min;
	adc_sum = adc_sum - adc_value_max;
	adc_sum = adc_sum>>3;
	return adc_sum;
}