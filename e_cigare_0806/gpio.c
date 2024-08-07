
#include "tenx_TM56F1522.h"
#include "tenx_TM56F1522_sfr.h"
#include "gpio.h"

/*---------------------------------------------------------------------------
  Symbol:
  P.P.->Push-Pull, O.D->Open Drain,P.O.D->Pseudo Open Drain, PU->Pull up
  Port0-> Enable Pull up resistor while P0OE.n=0 and P0.n=1
  ---------------------------------------------------------------------------
 定义GPIO 模式:
  sfr PAMOD10:Port A related @85H ->PA[1:0] Pin mode control
  sfr PAMOD32:Port A related @86H ->PA[3:2] Pin mode control
  sfr PAMOD54:Port A related @87H ->PA[5:4] Pin mode control
  sfr PAMOD76:Port A related @88H ->PA[7:6] Pin mode control
  
  sfr PBMOD10:Port B related @8CH ->PB[1:0] Pin mode control
  sfr PBMOD32:Port B related @8DH ->PB[3:2] Pin mode control
  sfr PBMOD54:Port B related @8EH ->PB[5:4] Pin mode control
  sfr PBMOD76:Port B related @8FH ->PB[7:6] Pin mode control
  
  sfr PDMOD10:Port D related @90H ->PD[1:0] Pin mode control
      ----------------------------------------------------------------
      PxMODE Hex  Px.n PinFunctionState  DigitalInput WKUP 
      
       0010  0x02  0   CmosOutLow          -           - 
       0110  0x06  0   CmosOutLow          -           -
	   1010  0x0A  0   CmosOutLow          -           -
 	   1110  0x0E  0   CmosOutLow          -           -
	   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       0010  0x02  1   CmosOutHigh         -           -        
       0110  0x06  1   CmosOutHigh         -           -        
       1010  0x0A  1   CmosOutHigh         -           - 
       1110  0x0E  1   CmosOutHigh         -           -  
       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       0000  0x00  0   OpenDrainLow        -           -   
	   0001  0x01  0   OpenDrainLow        -           -
	   0100  0x04  0   OpenDrainLow        -           -
       0101  0x05  0   OpenDrainLow        -           - 
       1000  0x08  0   OpenDrainLow        -           -
       1001  0x09  0   OpenDrainLow        -           -
       1100  0x0C  0   OpenDrainLow        -           -
       1101  0x0D  0   OpenDrainLow        -           - 
       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       0000  0x00  1   InputPU             Y           -
	   1000  0x08  1   InputPU_WK          Y           Y 
	   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	   0100  0x04  1   InputPD             Y           -
	   1100  0x0C  1   InputPD_WK          Y           Y 
       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       0001  0x01  1   InputHiz            Y           -
	   0101  0x05  1   InputHiz            Y           -
       1001  0x09  1   InputHiz_WK         Y           Y
       1101  0x0D  1   InputHiz_WK         Y           Y
	   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 //xx10  0x02  1   TK                  -           -  ？
	   xx10  0x02  0   CLD                 -           -   
       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	   0011  0x03  x    AnalogInputHiz     -           -
                      (ADC,CINx,CIPx,OPPx,
                        OPP  CMPx      )
		
       0111  0x07  x    CmosOut            -           -
                      (PWMx,TCOUT,T1OUT)

	   1011  0x0B  x     CmosOut           -           - 
                        (CTKCKO)
						
	   1111  0x0F  x      AnalogOut        -           -   
                       1/2 VCC (1/2 bias)    
 ------------------------------------------------------------------------------	
  PORTx:   PA	    PB	    PD
  	     	  
	PINx :Bit0~Bit7
        Bit0	  Bit1	  Bit2	  Bit3	  Bit4	  Bit5	  Bit6	  Bit7  
	      0x01	  0x02    0x04    0x08    0x10    0x20    0x40    0x80
  
  pinMode:
          Bit4     ->Px.n Pin State 
          Bit3~Bit0->Px.n Pin mode
          (Px=PA,PB,PD,n=0~7)
  ----------------------------------------------------------------------------------------*/ 
void PxMOD_Config(unsigned char PORTx,unsigned char PINx,GPIOx_PinMode_TypeDef pinMode) 
{                                                        
	unsigned char pinMod=0;
	
	pinMod=pinMode&0x0F;
	
	if(PORTx==GPIO_PA)             // PA.7~PA.0 pin      
	{
		if((PINx & Bit_0)==Bit_0)    // PA.0 pin
		{
			PAMOD10bits.PA0MOD=pinMod;			
		}
		
		if((PINx & Bit_1)==Bit_1)    // PA.1 pin
		{
			PAMOD10bits.PA1MOD=pinMod;
		}
		
		if((PINx & Bit_2)==Bit_2)    // PA.2 pin
		{
			PAMOD32bits.PA2MOD=pinMod;			
		}
		
		if((PINx & Bit_3)==Bit_3)    // PA.3 pin
		{
			PAMOD32bits.PA3MOD=pinMod;
		}
		
		if((PINx & Bit_4)==Bit_4)    // PA.4 pin
		{
			PAMOD54bits.PA4MOD=pinMod;			
		}
		
		if((PINx & Bit_5)==Bit_5)    // PA.5 pin
		{
			PAMOD54bits.PA5MOD=pinMod;
		}
		
		if((PINx & Bit_6)==Bit_6)    // PA.6 pin
		{
			PAMOD76bits.PA6MOD=pinMod;			
		}
		
		if((PINx & Bit_7)==Bit_7)    // PA.7 pin
		{
			PAMOD76bits.PA7MOD=pinMod;
		}
		
		if((pinMode&0xF0)==0x00)
		{
		  PAD&=~PINx;
		}
    else if((pinMode&0xF0)==0x10)
		{
		  PAD|= PINx;
		}
	}
	 
	if(PORTx==GPIO_PB)             // PB.7~PB.0 pin
	{
		if((PINx & Bit_0)==Bit_0)    // PB.0 pin
		{
			PBMOD10bits.PB0MOD=pinMod;			
		}
		
		if((PINx & Bit_1)==Bit_1)    // PB.1 pin
		{
			PBMOD10bits.PB1MOD=pinMod;
		}
		
		if((PINx & Bit_2)==Bit_2)    // PB.2 pin
		{
			PBMOD32bits.PB2MOD=pinMod;			
		}
		
		if((PINx & Bit_3)==Bit_3)    // PB.3 pin
		{
			PBMOD32bits.PB3MOD=pinMod;
		}
		
		if((PINx & Bit_4)==Bit_4)    // PB.4 pin
		{
			PBMOD54bits.PB4MOD=pinMod;			
		}
		
		if((PINx & Bit_5)==Bit_5)    // PB.5 pin
		{
			PBMOD54bits.PB5MOD=pinMod;
		}
		
		if((PINx & Bit_6)==Bit_6)    // PB.6 pin
		{
			PBMOD76bits.PB6MOD=pinMod;			
		}
		
		if((PINx & Bit_7)==Bit_7)    // PB.7 pin
		{
			PBMOD76bits.PB7MOD=pinMod;
		}
    
    if((pinMode&0xF0)==0x00)
		{
		  PBD&=~PINx;
		}
    else if((pinMode&0xF0)==0x10)
		{
		  PBD|= PINx;
		} 
	}
	 
	if(PORTx==GPIO_PD)             // PD.1~PD.0 pin
	{	
		if((PINx & Bit_0)==Bit_0)    // PD.0 pin
		{
			PDMOD10bits.PD0MOD=pinMod;		
		}
		 
		if((PINx & Bit_1)==Bit_1)    // PD.1 pin
		{
			PDMOD10bits.PD1MOD=pinMod;
		}
    
    if((pinMode&0xF0)==0x00)
		{
		  PDD&=~PINx;
		}
    else if((pinMode&0xF0)==0x10)
		{
		  PDD|= PINx;
		}		
	}	 
} 	

