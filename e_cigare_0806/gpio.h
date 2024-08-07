
#ifndef _gpio_H__
#define _gpio_H__


/*-----------------------------------------------------------------------------
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
  ---------------------------------------------------------------------------*/
typedef enum
{
  GPIOx_CmosOutL      = 0x02,  // 0x02,0x06,0x0A,0x0E
  GPIOx_CmosOutH      = 0x12,  // 0x12,0x16,0x1A,0x1E   
  
  GPIOx_OD_Low        = 0x01,  // 0x00,0x01,0x04,0x05,0x08,0x09,0x0C,0x0D
  GPIOx_InputPU       = 0x10,
  GPIOx_InputPD       = 0x14,
  GPIOx_InputHiz      = 0x11,  // 0x11,0x15
  
  GPIOx_InputPU_WKUP  = 0x18,
  GPIOx_InputPD_WKUP  = 0x1C,  
  GPIOx_InputHiz_WKUP = 0x19,  // 0x19,0x1D 
  
  GPIOx_CLD           = 0x02,  // xx10
  GPIOx_AnalogInputHiz= 0x23,  // ADC,CINx,CIPx,OPPx,CMPx,OPP
  GPIOx_PWMxTCOT1O    = 0x27,  // PWMx,TCOUT,T1OUT 
  GPIOx_CTKCKO        = 0x2B,  // CTKCKO  
  GPIOx_1_2VCC_Out    = 0x2F,  // AnalogOut 1/2 VCC (1/2 bias) 
}GPIOx_PinMode_TypeDef;

#define GPIO_PA 0
#define GPIO_PB 1
#define GPIO_PD 2

#define Bit_All               0xFF  // Bit All selected  
#define Bit_7                 0x80  // Bit 7 selected    
#define Bit_6                 0x40  // Bit 6 selected    
#define Bit_5                 0x20  // Bit 5 selected  
#define Bit_4                 0x10  // Bit 4 selected  
#define Bit_3                 0x08  // Bit 3 selected  
#define Bit_2                 0x04  // Bit 2 selected  
#define Bit_1                 0x02  // Bit 1 selected  
#define Bit_0                 0x01  // Bit 0 selected 

void PxMOD_Config(unsigned char PORTx,unsigned char PINx,GPIOx_PinMode_TypeDef pinMode);
/****************************************************************************************************/
#endif
