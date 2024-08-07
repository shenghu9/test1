/*
*******************************************************************************
Name		:tenx_TM56F1522_sfr.h
Version :V1.0
Author	:Lishuilan
Date		:2022.06.14
*******************************************************************************
*/

#ifndef _tenx_TM56F1522_sfr_H__
#define _tenx_TM56F1522_sfr_H__


//#include "tenx_TM56F1522.h"

/*----------------------------------------------------------------------------
  sfr STATUS[6:5]:RP       ->Register Bank Select for direct addressing @03H
  sfr PCLATH[4:3]:PCLATH4_3->for 4K/8K ROM   (ROM BANK) @0AH
      STATUS[6:5]:RP
      PCLATH[4:3]:PCLATH4_3 
         0    0  :Bank0
         0    1  :Bank1
         1    0  :Bank2
         1    1  :Bank3   
  ----------------------------------------------------------------------------*/
#define Bank0     0
#define Bank1     1
#define Bank2     2
#define Bank3     3

/*--------------------------------------------------------------------
  sfr CLKCTL:Fsys related @0FH:
  
      CLKCTL[7]:SCKTYPE->Slow Clock Type
                0: SIRC
                1: SXT
                
      CLKCTL[6]:FCKTYPE->Fast Clock Type
                0: FIRC
                1: FXT
                
      CLKCTL[4]:SLOWSTP->Stop Slow-clock after execute SLEEP instruction               
      CLKCTL[3]:FASTSTP->Stop Fast-clock
                0: no Stop
                1: Stop 
                
      CLKCTL[2]:CPUCKS->Select Fast-clock, System clock source is
                0: Slow-clock
                1: Fast-clock                                                
      
      CLKCTL[1:0]:CPUPSC->Fsys Prescaler
             0 0  Div8     
             0 1  Div4      
             1 0  Div2
             1 1  Div1
      ----------------------------------------------------------------       
  SysclkSrc  ->  Fsys
     0   0       SRC     
     0   1       SXT      
     1   0       FRC
     1   1       FXT
     
  SysclkPsc  ->  Fsys Prescaler 
     0   0       Div8     
     0   1       Div4      
     1   0       Div2
     1   1       Div1   
     
  Viceclk    ->  Vice clk 
     0           Disable
     1           Enable
  --------------------------------------------------------------------*/
#define ClkIRC    0
#define ClkEXT    1

#define FastClk   1
#define SlowClk   0

#define SysClkSrc_SRC   0    // 80KHz
#define SysClkSrc_SXT   1    // 32.768KHz
#define SysClkSrc_FRC   2    // 16 MHz
#define SysClkSrc_FXT   3    // 1~16MHz

#define SysclkPsc_Div16 0
#define SysclkPsc_Div4  1
#define SysclkPsc_Div2  2
#define SysclkPsc_Div1  3
  
/*----------------------------------------------------------------------------------
  sfr TM0CTL:Timer0 related @11H:
  sfr TM1CTL:Timer1 related @14H:
  
      TM0CTL[6]:TM0STP->Stop Timer0
      TM1CTL[6]:TM1STP->Stop Timer1
                        0: Timerx runs  (x=0,1)
                        1: Timerx stops (x=0,1)
                        
      TM0CTL[5]:TM0EDG->TM0CKI (PA2) edge
                        0: rising edge
                        1: falling edge
                        
      TM0CTL[4]:TM0CKS->Timer0 prescaler clock source
                        0: Fsys/2
                        1: TM0CKI (PA2)
                        
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
------------------------------------------------------------------------------------*/
//uchar Timer0Reload   @0x3B  : FPLANE;
//uchar Timer1Reload   @0x3B  : FPLANE;

/*----------------------------------------------------------------------------------
  sfr T2CTL:T2 related @15H:
  
      T2CTL[4  ]:T2CLR->T2 counter clear
                        0: T2 runs
                        1: T2 clear and hold
                        
      T2CTL[3:2]:T2CKS->T2 clock source
                        00: Slow-clock 
                        01: Fsys/128 
                        1x: FIRC/512 (16 MHz/512)
                        
      T2CTL[1:0]:T2PSC->T2 prescaler,T2 clock source divided by
                        00: 32768 
                        01: 16384 
                        10: 8192 
                        11: 128                  
  ------------------------------------------------------------------------------------*/
#define TM2CKS_SCK          0
#define TM2CKS_FsysDiv128   1
#define TM2CKS_FRC_Div512   2

#define TM2PSC_Div32768     0
#define TM2PSC_Div16384     1
#define TM2PSC_Div8192      2
#define TM2PSC_Div128       3
 
/*----------------------------------------------------------------------------------
  sfr LVCTL:LVD/LVR related @16H:
      
      LVCTL[7  ]:LVDF  ->Low voltage detection flag
                         0: VCC > VLVD
                         1: VCC < VLVD
      LVCTL[6  ]:LVDHYS->LVD Hystertsis, 25mV@LVD=2.19V, 70mV@LVD=4.15V (tt)
                         0: disable
                         1: enable
  
      LVCTL[5  ]:LVRSAV->POR/LVR auto power off in STOP/IDLE mode
                         0: POR/LVR enable
                         1: POR/LVR enable in Slow/Fast mode, disable in STOP/IDLE mode
                           (PORPD=1, POR force disable. 
                            LVRPD=1, LVR force disable)
                        
      LVCTL[4  ]:LVDSAV->LVD auto power off in STOP/IDLE mode
                         0: LVD enable
                         1: LVD enable in Slow/Fast mode,disable in STOP/IDLE mode 
                                           
      LVCTL[3:0]:LVDS  ->LVD voltage (VLVD) select (TBD)
                         0000:Disable
                         0001:2.19V 
                         0100:2.61V 
                         1000:3.17V 
                         1100:3.73V
                         1111:4.15V(TBD)
  ------------------------------------------------------------------------------------*/
#define LVDS_Disable  0
#define LVDS_2V19     1
#define LVDS_2V33     2
#define LVDS_2V47     3
#define LVDS_2V61     4
#define LVDS_2V75     5
#define LVDS_2V89     6
#define LVDS_3V03     7
#define LVDS_3V17     8
#define LVDS_3V31     9
#define LVDS_3V45     10
#define LVDS_3V59     11
#define LVDS_3V73     12
#define LVDS_3V87     13
#define LVDS_4V01     14
#define LVDS_4V15     15

      
//#define Read_LVDF()  (return LVDF)                       

/*----------------------------------------------------------------------------------
  sfr ADCTL:ADC related @18H:
      
      ADCTL[7:4]:ADCDL  ->ADC output data bit 3~0,only Read
                         
      ADCTL[3  ]:ADST->ADC start bit.
                         0: H/W clear after end of conversion
                         1: ADC start conversion
  
      ADCTL[2:0]:ADCKS->ADC clock frequency selection. 1MHz(Typ.)
                        000: Fsys/256
                        001: Fsys/128 
                        010: Fsys/64
                        011: Fsys/32 
                        100: Fsys/16
                        101: Fsys/8 
                        110: Fsys/4                     
                        111: Fsys/2
  --------------------------------------------------------------------------                  
  sfr ADCTL2:ADC related @19H:
      
      ADCTL2[7:6]:ADVREFS->ADC Vref select. 
                           00: VCC
                           01: 2.5207V
                           10: 3.0379V
                           11: 4.0646V
                                           
      ADCTL2[4:0]:ADCHS  ->ADC channel select
                           00000: ADC0 (PA0)
                           00001: ADC1 (PA1)
                           00010: ADC2 (PA2)
                           00011: ADC3 (PA3)
                           00100: ADC4 (PA4)
                           00101: ADC5 (PA5)
                           00110: ADC6 (PA6)
                           00111: ADC7 (PB0)                            
                           01000: ADC8 (PB1) 
                           01001: ADC9 (PB2)
                           01010: ADC10(PB4)
                           01011: ADC11(PB5) 
                           01100: ADC12(PB6) 
                           01101: ADC13(PB7) 
                           01110: VBGO
                           01111: OPO
                           10111: 1/4 VCC
                           others: Reserved                
------------------------------------------------------------------------------------*/
#define ADC_Start()         ADST=1

#define ADCKS_FsysDiv256    0
#define ADCKS_FsysDiv128    1
#define ADCKS_FsysDiv64     2
#define ADCKS_FsysDiv32     3
#define ADCKS_FsysDiv16     4
#define ADCKS_FsysDiv8      5
#define ADCKS_FsysDiv4      6
#define ADCKS_FsysDiv2      7

#define ADVREFS_VCC         0
#define ADVREFS_2V52        1
#define ADVREFS_3V03        2
#define ADVREFS_4V06        3 

#define ADCHS_PA0_ADC0      0
#define ADCHS_PA1_ADC1      1
#define ADCHS_PA2_ADC2      2
#define ADCHS_PA3_ADC3      3
#define ADCHS_PA4_ADC4      4
#define ADCHS_PA5_ADC5      5
#define ADCHS_PA6_ADC6      6
#define ADCHS_PB0_ADC7      7
#define ADCHS_PB1_ADC8      8
#define ADCHS_PB2_ADC9      9
#define ADCHS_PB4_ADC10     10
#define ADCHS_PB5_ADC11     11
#define ADCHS_PB6_ADC12     12
#define ADCHS_PB7_ADC13     13
#define ADCHS_VBG_ADC14     14
#define ADCHS_OPO_ADC15     15
#define ADCHS_1_4VCC_ADC16  23

/*----------------------------------------------------------------------------------
  sfr TKCTL:CTK related @1EH:
      
      TKCTL[7  ]:TKFJMP ->CTK clock frequency auto change select;  
                          0: disable, determin by SFR JMPVAL
                          1: enable, auto-change
                         
      TKCTL[6:4]:JMPVAL ->CTK clock frequency select
                          (only available in TKFJMP=0)
                          
                         
  
      TKCTL[2:0]:CTKREFC->CTK conversion time (CX2, CX1, CX0): 
                          0: smallest
                          7: longest
  --------------------------------------------------------------------------                  
  sfr TKCTL2:CTK related @1FH:
      
      TKCTL2[7]:CTKPD->CTK Touch Key Power Down
                       0: CTK enable
                       1: CTK disable
                       
      TKCTL2[6]:TKSOC->Touch Key start of conversion,HW clear while end of conversion
                       0: disable
                       1: enable, Touch Key start conversion
                       
      TKCTL2[5]:TKEOC->Touch Key end of conversion flag
                       TKSOC may have 5us delay after TKSOC=1
                       so F/W must wait enough time before polling this flag.
                       0: Indicates conversion is in progress
                       1: Indicates conversion is finished
                                           
      TKCTL2[3:0]:TKCHS ->Touch Key Channel Select
                          0000: TK0 (PD0)
                          0001: TK1 (PA1)
                          0010: TK2 (PA4)
                          0011: TK3 (PA5)
                          0100: TK4 (PA2)
                          0101: TK5 (PA0)
                          0110: TK6 (PA6)                          
                          0111: TK7 (PB0)    
                          1000: TK8 (PB1)
                          1001: TK9 (PB2)
                          1010: TK10(PB3)
                          1011: TK11(PB4)
                          1100: TK12(PB5)                       
                          1101: TK13(PB6)
                          1110: TK14(PB7)
                          1111: Internal Reference
 ------------------------------------------------------------------------------------*/
#define CTKJMP_VAL0        0
#define CTKJMP_VAL1        1
#define CTKJMP_VAL2        2
#define CTKJMP_VAL3        3
#define CTKJMP_VAL4        4
#define CTKJMP_VAL5        5
#define CTKJMP_VAL6        6
#define CTKJMP_VAL7        7
#define CTKJMP_AutoChange  8

#define CTKREFC_Smallest 0
#define CTKREFC_Smaller  1
#define CTKREFC_Small    2
#define CTKREFC_Middle1  3
#define CTKREFC_Middle2  4
#define CTKREFC_Long     5
#define CTKREFC_Longer   6
#define CTKREFC_Longest  7 
 
#define TKCHS_PD0_TK0   0
#define TKCHS_PA1_TK1   1
#define TKCHS_PA4_TK2   2
#define TKCHS_PA5_TK3   3
#define TKCHS_PA2_TK4   4
#define TKCHS_PA0_TK5   5
#define TKCHS_PA6_TK6   6
#define TKCHS_PB0_TK7   7
#define TKCHS_PB1_TK8   8
#define TKCHS_PB2_TK9   9
#define TKCHS_PB3_TK10  10
#define TKCHS_PB4_TK11  11
#define TKCHS_PB5_TK12  12
#define TKCHS_PB6_TK13  13
#define TKCHS_PB7_TK14  14

//#define TKC_Start()     TKSOC=1
//#define Read_TKEOC_f()  (return TKEOC)

                         
/*----------------------------------------------------------------------------------
  sfr OPTION:STATUS INT0 INT1 WDT WKT related @81H:
      
      OPTION[7]:HWAUTO ->Save Restore STATUS w/o TO, PD   
                          (Hi-tech C don’t need, set this bit = 0)
                           0:disable
                           1:enable
                           
      OPTION[6]:INT0EDG ->INT0 pin edge interrupt event
      OPTION[5]:INT1EDG ->INT1 pin edge interrupt event
                          0: falling edge to trigger
                          1: rising  edge to trigger                                        
                         
      OPTION[3:2]:WDTPSC->WDT Period @5V
                          00: 102ms
                          01: 205ms
                          10: 819ms
                          11: 1638ms                       
                         
      OPTION[1:0]:WKTPSC->WKT Period @3V
                          00: 13ms
                          01: 26ms
                          10: 51ms
                          11: 102ms 
                          
      -----------------------------------------------------------------
  sfr OPTION2:PWM0 INT2 INT1 INT0 related @91H:
      
      OPTION2[2]:INT2SEL ->INT2 pin select
                           0: PA7
                           1: PB5
                           
      OPTION2[1]:INT1SEL ->INT1 pin select
                           0: PA1
                           1: PB1
                           
      OPTION2[0]:INT0SEL ->INT0 pin select
                           0: PA3
                           1: PB2                            
  ------------------------------------------------------------------------------------*/
#define INTxEDG_Falling 0  // x=(0,1)
#define INTxEDG_rising  1  // x=(0,1)

#define WDTPSC_102ms    0
#define WDTPSC_205ms    1
#define WDTPSC_819ms    1
#define WDTPSC_1368ms   3

#define WKTPSC_13ms     0
#define WKTPSC_26ms     1
#define WKTPSC_51ms     1
#define WKTPSC_102ms    3

#define INT2SEL_PA7     0
#define INT2SEL_PB5     1

#define INT1SEL_PA1     0
#define INT1SEL_PB1     1

#define INT0SEL_PA3     0
#define INT0SEL_PB2     1

     
/*----------------------------------------------------------------------------------
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
	 //xx10  0x02  1   TK                  -           -  £¿
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
  ------------------------------------------------------------------------------------*/

    
/*----------------------------------------------------------------------------------
  sfr OPTION2:PWM0 INT2 INT1 INT0 related @91H:
  
      OPTION2[5:4]:PWMCKS->PWM Clock Source
                           0x: Fsys
                           10: FIRC (16 MHz)
                           11: FIRC*2 (32 MHz)  
      -----------------------------------------------------------------
  sfr PWMCTL:PWM0 related @89H: 
      
      PWMCTL[7]:PWMEN    ->PWM Clock Enable
                           0: Disable
                           1: Enable
 
      PWMCTL[5:4]:PWM0OM ->PWM0 output mode
                           00: Mode0
                           01: Mode1
                           10: Mode2
                           11: Mode3                                     
                         
                      
      PWMCTL[1:0]:PWM0DZ ->PWM0 non-overlap control
                           0000: no non-overlap
                           0001: non-overlap width are 1 PWM clock cycle
                           0010: non-overlap width are 2 PWM clock cycles
                           ...
                           1111: non-overlap width are 15 PWM clock cycles 
                            
  ------------------------------------------------------------------------------------*/
#define PWMCLKSRC_Fsys  0
#define PWMCLKSRC_1FIRC 2
#define PWMCLKSRC_2FIRC 3

#define PWM0OM_Mode0    0
#define PWM0OM_Mode1    1
#define PWM0OM_Mode2    2
#define PWM0OM_Mode3    3

#define PWM0DZ_None     0
#define PWM0DZ_Pwmclk1  1
#define PWM0DZ_Pwmclk2  2
#define PWM0DZ_Pwmclk3  3
#define PWM0DZ_Pwmclk4  4
#define PWM0DZ_Pwmclk5  5
#define PWM0DZ_Pwmclk6  6
#define PWM0DZ_Pwmclk7  7
#define PWM0DZ_Pwmclk8  8

#define PWM0DZ_Pwmclk9  9
#define PWM0DZ_Pwmclk10 10
#define PWM0DZ_Pwmclk11 11
#define PWM0DZ_Pwmclk12 12
#define PWM0DZ_Pwmclk13 13
#define PWM0DZ_Pwmclk14 14
#define PWM0DZ_Pwmclk15 15

/*----------------------------------------------------------------------------------
  sfr OPVBGOREG:VBG OP output related @105H:
      
      OPVBGOREG[1]:OPOE -> OPO output to PA3 Enable
                         0: Disable
                         1: Enable
                           
      OPVBGOREG[0]:VBGOE-> VBG1.25V output to PA3 Enable
                        (need to set PA3MOD= MODE3 & VREN=1)
                         0: Disable
                         1: Enable               
  ------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------
  sfr OPCTL:OPA @108H:
      
      OPCTL[7  ]:PDOPA -> OPA power down enable control
                          0: disable OPA power down(OPA enable )
                          1: enable  OPA power down(OPA disable)
                           
      OPCTL[6:5]:SOPP  -> OPA P input select
                          00: OPP input source is PD0
                          01: OPP input source is PD1
                          10: OPP input source is PA2
                          11: OPP input source is AVSS
                        
      OPCTL[4  ]:SOTV  -> OPA N input voltage select in Comparator mode
                          0: AVSS
                          1: VBG (voltage level is selected by ADVREFS)
                           
      OPCTL[3:2]:SOPG  -> Select OPA gain
                          00: 1X
                          01: 20X
                          10: 50X
                          11: 100X
                        
      OPCTL[1:0]:SOPM  -> Select OPA operating mode
                          00: Normal mode
                          01: Trim 1 mode
                          10: Trim 2 mode
                          11: Comparator mode                                                                     
  ------------------------------------------------------------------------------------*/
#define OPA_PinSel_PD0   0
#define OPA_PinSel_PD1   1
#define OPA_PinSel_PA2   2
#define OPA_PinSel_AVSS  3

#define OPA_VolSel_AVSS  0
#define OPA_VolSel_VBG   1

#define OPA_Gain_1x      0
#define OPA_Gain_20x     1
#define OPA_Gain_50x     2
#define OPA_Gain_100x    3

#define OPA_Mode_Normal  0
#define OPA_Mode_Trim1   1
#define OPA_Mode_Trim2   2
#define OPA_Mode_Compare 3

/*----------------------------------------------------------------------------------
  sfr LVRPD:LVR POR related @109H:
   
   Write:
         Write 37h to force LVR+POR Disable
         Write 38h to force LVR Disable, POR still enable
         Write 39h to force POR Disable, LVR still enable
         Write others LVR and POR enable   
  
   Read:   
      LVRPD[1]:PORPDF -> POR force power down flag
                         0: Disable(POR enable)
                         1: Enable (POR is forced power down)
                           
      LVRPD[0]:LVRPDF-> LVR force power down flag
                         0: Disable(LVR enable)
                         1: Enable (LVR is forced power down)               
  --------------------------------------------------------------------------------*/
//#define LVRDIS_PORDis()   LVRPD=0x37
//#define LVRDIS_POREN()    LVRPD=0x38  
//#define LVREN_PORDis()    LVRPD=0x39
//#define LVREN_POREN()     LVRPD=0x00

//#define Read_PORPD_FLAG() return(PORPD)
//#define Read_LVRPD_FLAG() return(LVRPD0)
         
/*----------------------------------------------------------------------------------
  sfr TABR:Table Read related @18CH:
   
      1. TABR write 01H = instruction TABRL
      2. TABR write 02H = instruction TABRH
      3. After step.1 or step.2, read TABR to get main ROM table read value
         After step.1, read TABR to get EEPROM value (when EEPEN = E2h)
         Table Read for ASM: instruction TABRL / TABRH or register TABR
         Table Read for C  : using register TABR              
  ------------------------------------------------------------------------------------*/

        
/*----------------------------------------------------------------------------------
  sfr CMPCTL:Comparator related @18DH:
   
      CMPCTL[7]:PDCMP -> Comparator power down enable control
                          0: disable (CMP enable )
                          1: enable  (CMP disable)
                           
      CMPCTL[6]:CMPO  -> Comparator output status
                          0: CIP < CIN
                          1: CIP > CIN or PDCMP=1                         
                          
      CMPCTL[5]:CMPOE -> Comparator output (CMPO) signal output to PA5
                          0: disable
                          1: enable, PA5MOD should be set to xx10b  (after CMPINV)                                              
                        
      CMPCTL[4]:CMPINV -> Comparator output (CMPO) invert control
                          0: disable
                          1: enable
                           
      CMPCTL[3:2]:CMPTRIG -> Comparator interrupt trigger direction
                             00: Rising  edge  trigger (When CMPINV=0)
                             01: Falling edge  trigger (When CMPINV=0)
                             10: Both    edge
                             11: High    level trigger (When CMPINV=0)
                        
      CMPCTL[1:0]:CMPDBS  -> Comparator output de-bounce time
                             00: none
                             01: 4  Fsys
                             10: 8  Fsys
                             11: 16 Fsys             
  --------------------------------------------------------------------------------*/
#define CMPO_CIPlessCIN      0
#define CMPO_CIPmoreCIN      1
  
#define CMPTRIG_RisingInt    0
#define CMPTRIG_FallingInt   1
#define CMPTRIG_BothEdge     2
#define CMPTRIG_HigeLevelInt 3

#define CMPDBS_None          0
#define CMPDBS_4Fsys         1
#define CMPDBS_8Fsys         2
#define CMPDBS_16Fsys        3
    
/*----------------------------------------------------------------------------------
  sfr CMPPNS:Comparator DAC OPA related @18EH:
   
      CMPPNS[7]:SCMPN  -> internal DAC output connect to Comparator control
                          0:                CINx connect to comparator N port
                          1: internal DAC output connect to comparator N port
                           
      CMPPNS[6:4]:SCIN -> Comparator N input select
                          000: CIN1 connect to comparator N port
                          001: CIN2 connect to comparator N port                    
                          010: CIN3 connect to comparator N port
                          011: CIN4 connect to comparator N port
                          1xx: NC
                         
      CMPPNS[3]:OPOF   -> OPA output (OPO) connect to Comparator control
                          0:OPO    connect to comparator P port
                          1:OPO disconnect to comparator P port                             
                        
      CMPPNS[2:0]:SCIP -> Comparator P input select
                          000: CIP1 connect to comparator P port
                          001: CIP2 connect to comparator P port                    
                          010: CIP3 connect to comparator P port
                          011: CIP4 connect to comparator P port
                          1xx: NC            
  --------------------------------------------------------------------------------*/
#define CMPN_Src_CINx      0    
#define CMPN_Src_DACO      1

#define CMPN_Src_CIN1_PA3  0
#define CMPN_Src_CIN2_PA0  1
#define CMPN_Src_CIN3_PB7  2
#define CMPN_Src_CIN4_PB4  3

#define CMPP_Src_OPO       0    
#define CMPP_Src_CIPx      1

#define CMPP_Src_CIP1_PA1  0
#define CMPP_Src_CIP2_PA2  1
#define CMPP_Src_CIP3_PB6  2
#define CMPP_Src_CIP4_PD1  3

/*----------------------------------------------------------------------------------
  sfr DACTL:DAC/Comparator related @18FH:
   
      DACTL[7]:SVRF  -> Select comparator reference voltage level
                        0:VDDA
                        1:VBGO
                           
      DACTL[6:0]:SVL -> Select DAC output voltage 
                        reference source can be selected as VDDA or VBGO
                        000_0000: 0/128 * reference source
                        000_0001: 1/128 * referencee source
                        ...
                        111_1101: 125/128 * reference source
                        111_1110: Reserved
                        111_1111: Reserved
  ------------------------------------------------------------------------------------*/
#define DAC_VrefSrc_VDDA  0
#define DAC_VrefSrc_VBGO  1

#define DAC_OutVolt_Min   0
#define DAC_OutVolt_Max   125

/*----------------------------------------------------------------------------------
  sfr EEPCTL:EEPROM related @190H:
   
      EEPCTL[7]:EEPTO   -> EEPROM Write Time-Out flag
                           0:EEPROM Write no Time-Out
                           1:EEPROM Write is Time-Out
                           
      EEPCTL[1:0]:EEPTE -> EEPROM Write Time-Out Enable. 
                           00: Disable
                           01: 1.5ms
                           10: 5.8ms
                           11: 11.7ms
      ------------------------------------------------------
  sfr EEPEN:EEPROM related @191H:
            EEPROM Access Enable
            Write 0xE2 to this register will enable EEPROM access
            Write others value to this register will disable EEPROM access    
       
                           
  ------------------------------------------------------------------------------------*/
#define EEPTO_None     0
#define EEPTO_1500us   1
#define EEPTO_5800us   2
#define EEPTO_11700us  3
                
/*------------------------end-----------------------------------------------*/ 

#endif