/*--------------------------------------------------------------------------
SMOKEDETECTOR.C

Code file for generic 80C51 and 80C31 microcontroller.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#include"SmokeDetector.h"

extern UINT_8 PWMC[4];//四路PWM脉宽控制变量，在PWM中定义

UINT_8 warningSec[4]=0;
UINT_8 sleepSec[4]=0;
UINT_8 timer1Count=0;

float smokeCode[4];
struct MODE Detector[4];

void SmokeDetectorInit()
{
	UINT_8 i;
	for(i=0;i<4;i++)
	{
		smokeCode[i]=0;
		Detector[i].sleepTime=10;
		Detector[i].warningTime=10;
		Detector[i].enableConcentration=10;
		Detector[i].fanStartConcentration=20;		
	}
	P0&=0xf0;//将P0^0-3位置0，其它位不变

	TMOD|=0x10;//模式1
	TH1=0x3c;
	TL1=0xb0;//装入15536，中断频率20Hz
	EA=1;//开总中断
	ET1=1;//开定时器1中断
	TR1=1;//启动定时器0
}

void SmokeDetector()
{
	UINT_8 num;
	//float voltage;
	UINT_8 i;
	for(i=0;i<4;i++)
	{
		num=ReadADC(i);//读取第i路电压值，范围是0-255
		num=ReadADC(i);//连续读3次，使读数稳定
		num=ReadADC(i);
		//voltage=(float)num*5/256; //根据参考电源VREF算出时间电压
		//sprintf(temp,"V0 %3.2f ",voltage);//格式输出电压值
		smokeCode[i]=(float)num*100/256; //根据参考电源VREF算出浓度百分比
	}
}

void SetWarning()
{
	
	UINT_8 i;
	for(i=0;i<4;i++)
	{
		if(smokeCode[i]>Detector[i].enableConcentration)
		{
			if(warningSec[i]==0 && sleepSec[i]==0)//若P0^i是为低电平,且不在睡眠时间
			{
				P0|=(0x01<<i);//将P0^i位置1，其它位不变
				warningSec[i]=1;
			}
			else
			{	
				
				if(warningSec[i]>=Detector[i].warningTime)
				{
					warningSec[i]=0;
					sleepSec[i]=1;
					P0&=((0xfe<<i)|(0xfe>>(8-i)));//将P0^i位置0，其它位不变
				}
				if(sleepSec[i]>=Detector[i].sleepTime)
				{
					sleepSec[i]=0;
					P0|=(0x01<<i);//将P0^i位置1，其它位不变
					warningSec[i]=1;
				}
			}
		}
		else
		{
			P0&=((0xfe<<i)|(0xfe>>(8-i)));//将P0^i位置0，其它位不变
			warningSec[i]=0;
			sleepSec[i]=0;
		}
	}	
}

void SetPWMxC()
{
	UINT_8 i;
	for(i=0;i<4;i++)
	{
		if(smokeCode[i]>Detector[i].fanStartConcentration)
		{
			if(smokeCode[i]>70)
			{
				PWMC[i]=4;
			}
			else if(smokeCode[i]>60)
			{
				PWMC[i]=3;
			}
			else if(smokeCode[i]>50)
			{
				PWMC[i]=2;
			}
			else
			{
				PWMC[i]=1;
			}
		}
		else
		{
			PWMC[i]=0;
		}
	}
		
}

 void TIMER_1() interrupt 3//定时器1中断入口
{
	UINT_8 i;
	timer1Count++;
	if(timer1Count==20)
	{
		timer1Count=0;
		for(i=0;i<4;i++)
		{
			if(warningSec[i] && warningSec[i]!=255)
			{
				warningSec[i]++;
			}
			if(sleepSec[i] && sleepSec[i]!=255)
			{
				sleepSec[i]++;
			}
		}
	}
	TH1=0x3c;
	TL1=0xb0;//装入15536，中断频率20Hz	
}