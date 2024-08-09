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

//添加代码
//#define Rload_1ms  5
//#define VREF 2480
#define VMIN 3000
#define VMAX 4200

unsigned int ADC_VAL = 0;
unsigned char Smoke_Cnt=0;
unsigned int event;
unsigned int Bat_Volt;
unsigned int Bat_percent;

unsigned int ten;
unsigned int one;
extern unsigned int mark_state;

void charge_scan();
unsigned int Adc_Value_to_Voltage();

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

    Adc_Init(AdcClk_Div16,AdcVref_2P48V,AdcChanel_PA2);    //ADC频率小于1M
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
          //HW_Led_Scan(ten,one);
       }
       
       if(event & EVENT_20ms)   //20ms执行一次
       {
          event_clr(EVENT_20ms);
          charge_scan();       //充电检测
          if(event & EVENT_CHARGE)
          {
              mark_state |= 0x01;     //充电显示
          }
          else
          {
              //电池电压4200mv为满电，低于3000mv时为低电，mcu不工作
              //Bat_Volt = Adc_Value_to_Voltage();    //电池电压为2倍的adc值 (mv)
              //((Bat_Volt*2)-3000)/1200;       //当前电量百分比
              ten = (Adc_Value_to_Voltage())/10;       //十位
              one = (Adc_Value_to_Voltage())%10;     //个位

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
      if(Smoke_Cnt < 50)
      {
         mark_state = 0xFE;    //烟油状态全亮3格
      }else if(Smoke_Cnt < 100)
      {
         mark_state = 0xDE;    //烟油状态2格
      }else if(Smoke_Cnt < 150)
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
           Cnt_1s = 0;
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

unsigned int Adc_Value_to_Voltage()
{
    unsigned int voltage;
    ADC_VAL = Adc_Get_Average();
    voltage = (ADC_VAL * VREF)/4095;    //参考电压：vcc2.48v 2480mv
    Bat_percent = ((voltage*2 -VMIN) * 100) / (VMAX - VMIN);
    //Bat_percent = (Bat_percent + 5)/10;   //四舍五入到最接近的百分比
    if(Bat_percent < 0)
    {
       Bat_percent = 0;
    }
    if(Bat_percent >= 100)
    {
       Bat_percent = 99;
    }
    return Bat_percent;
}
