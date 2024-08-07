
#include "tenx_TM56F1522.h"
#include "Sys_Bsp.h"
#include "gpio.h"

/*
**************************************************************************************************
系统时钟=快钟(慢钟开启)
系统时钟=慢钟(快钟停止)
**************************************************************************************************
*/

void Bsp_SysClock_Config(SCK_TypeDef SlowClk,FCK_TypeDef FastClk,SysClk_TypeDef SysClk,SysClkPsc_TypeDef SysClkPsc)
{
	if((SlowClk==SCK_SXT)||(FastClk==FCK_FXT))
	{
		PxMOD_Config(GPIO_PA,Bit_5|Bit_4,GPIOx_InputPU);
	}

	if(CPUCKS==0)                       // Slow Clock Now                           
	{
	  FCKTYPE=(bit)(FastClk==FCK_FXT);	// Fast clock select to FRC/FXT
	 	FASTSTP=0;		 	                  // Fast clock Enable
	  asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	  CPUCKS=1;				                  // Change Fsys to Fast clock
 
	  SCKTYPE=(bit)(SlowClk==SCK_SXT);	// Slow clock select to SRC/SXT
	 	SLOWSTP=0;	                      // Slow clock Enable
	}
	else    // Fast Clock Now
	{
	  SCKTYPE=(bit)(SlowClk==SCK_SXT);	// Slow clock select to SRC/SXT
	  SLOWSTP=0;		                   	// Slow clock Enable
  	asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	 	CPUCKS=0;				                  // Change Fsys to Slow clock
	  FCKTYPE=(bit)(FastClk==FCK_FXT);	// Fast clock select to FRC/FXT
	 	FASTSTP=0;		                    // Fast clock Enable  
	}
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
 
	if(SysClk==SysClk_FCK)
	{
		CPUCKS=1;				                 // Change Fsys to Fast clock
	}
	else
	{
		CPUCKS=0;				                 // Change Fsys to Slow clock
		FASTSTP=1;			                 // Fast clock Disable
	}
	CLKCTLbits.CPUPSC=SysClkPsc;
}

/*
**************************************************************************************************
*/