//#include <pic.h>
#include "tenx_TM56F1522.h"
#include "Sys_Bsp.h"
#include "gpio.h"
#include "Timerx.h"
#include "adc.h"
#include "ISR.h"
#include "led.h"
#include "INTx.h"
#include "EEPROM.h"
#include "wktwdt.h"


const unsigned int szTemp @0x0FFE=0;//Don't remove or remark this line.

#define Rload_1ms  5
unsigned int ADC_VAL = 0;
unsigned char Smoke_Cnt=0;
unsigned int event;
extern unsigned int mark_state;

void charge_scan();


//--------------------------------------
//main function
void main(void)
{
    /*-------------------------------------------------
    Write 37h to force LVR+POR Disable
    Write 38h to force LVR Disable, POR still enable
    Write 39h to force POR Disable, LVR still enable
    Write others LVR and POR enable
    -------------------------------------------------*/
    LVRPD  =0; 
      
    LVRSAV =1; // POR/LVR auto power off in STOP/IDLE mode
    LVDSAV =1; // LVD auto power off in STOP/IDLE mode
    PDCMP  =0; // Disable Comparator & DAC power down ee部分

    Bsp_SysClock_Config(SCK_SRC,FCK_FRC,SysClk_FCK,SysClkPsc_Div1);
    LED_Init();         //IO引脚初始化

    Timer0_Init(TM0_FsysDiv2,TM01_ClkPsc_32,Rload_1ms);
    //Wdt_Init(WKTWdtPsc_Div4);

    Adc_Init(AdcClk_Div2,AdcVref_VCC,AdcChanel_PA2);
    INTx_Init(ExINT0,INTxPin_PA,INTxEDG_Rising);
    Interrupt_EnConfig(IntSrc_TMR0|IntSrc_INT0);

    TM0Cnt_En(Enable);

    Smoke_Cnt = EEPROM_ReadByte(0);
    
    mark_state = 0xFE;

    while(1)
    {
       if(event & EVENT_TIME0)   //1ms执行一次
       {
          event_clr(EVENT_TIME0);
          HW_Led_Scan(1,0);
       }
       
       if(event & EVENT_20ms)   //20ms执行一次
       {
          event_clr(EVENT_20ms);
          charge_scan();       //充电检测
          if(event & EVENT_CHARGE)
          {
              
          }
          else
          {
              ADC_VAL = Adc_Get_Average();
          }
          
       }
       

        if(event & EVENT_Power_Off)    //进入停止模式
        {
            SLOWSTP=0;   //0:空闲模式   1:停止模式
            asm("sleep");
            asm("nop");
            asm("nop");
            asm("CLRWDT"); // clear wdt 
        }
      
    
    }
}


unsigned int Cnt_20ms = 0;
unsigned int Cnt_1s = 0;
//--------------------------------------
void interrupt Int_ISR(void)  
{
	if(TM0IF==1)
	{	
	  TM0IF=0;
    event_set(EVENT_TIME0);
    if(++ Cnt_20ms >= 20)
    {
       Cnt_20ms = 0;
       event_set(EVENT_20ms);
    }

  }

  if(INT0IF==1)   //外部中断 检测到抽烟
	{	
	  Smoke_Cnt ++;
    EEPROM_WriteByte(Smoke_Cnt,0);
    if(Smoke_Cnt < 200)
    {
       mark_state = 0xFE;    //烟油状态全亮3格
    }else if(Smoke_Cnt < 400)
    {
       mark_state = 0xDE;    //烟油状态2格
    }else if(Smoke_Cnt < 600)
    {
       mark_state = 0x9E;    //烟油状态1格
    }else
    {
       mark_state = 0x02;
    }
	  INT0IF=0;
  }

}

void charge_scan()
{
     if(PD1 == 1)
     {
        if(++ Cnt_1s > 50)
        {
           if(PD1 == 1)
           {
              event_set(EVENT_CHARGE);
           }
        }
     }
     else
     {
         Cnt_1s = 0;
         event_clr(EVENT_CHARGE);
     }
}
