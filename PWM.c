/*--------------------------------------------------------------------------
PWM.C
Code file for generic 80C51 and 80C31 microcontroller, put out PWM waves with P0^4~7, use Timer 0 Mode 2.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#include"PWM.h"

/*定义PWM占空比控制参数，目前提供四档变化*/
UINT_8 PWMC[4]=0;
UINT_8 pwmCount=0;

/*调试用粗略时钟参数*/
#ifdef __DEBUG__
UINT_16 timer0IntCount;
UINT_8 second;
UINT_8 minute;
UINT_8 hour;
UINT_8 day;

static void __Clock();//粗略的时钟函数，仅供检测用
#endif

static void __PWMControl();//PWM主控函数，只能由定时器0中断调用！！

void PWMInit()//PWM初始化函数，使用定时器0
{
	#ifdef __DEBUG__
	second=0;
	minute=0;
	hour=0;
	day=0;
	timer0IntCount=0;
	#endif

	PWM0=0;
	PWM1=0;
	PWM2=0;
	PWM3=0;
	TMOD|=0x02;//模式2，自动重装,因定时器中断操作较多，模式2更准确
	TH0=0x06;
	TL0=0x06;//装入6，中断频率4kHz，实现4档1kHzPWM波形输出
	EA=1;//开总中断
	ET0=1;//开定时器0中断
	TR0=1;//启动定时器0
}

static void __PWMControl()//PWM主控函数，只能由定时器0中断调用！！
{
	pwmCount++;
	if(pwmCount>3)	{pwmCount=0;}
	if(((int)pwmCount-(int)PWMC[0])>=0)	{PWM0=0;}
	else {PWM0=1;} 
	if(((int)pwmCount-(int)PWMC[1])>=0)	{PWM1=0;}
	else {PWM1=1;}
	if(((int)pwmCount-(int)PWMC[2])>=0)	{PWM2=0;}
	else {PWM2=1;}
	if(((int)pwmCount-(int)PWMC[3])>=0)	{PWM3=0;}
	else {PWM3=1;}
	
	#ifdef __DEBUG__
	__Clock();
	#endif

	//TH0=0xff;
	//TL0=0x06;//装入ff06，65286，中断频率4kHz
}

#ifdef __DEBUG__
void __Clock()//粗略的时钟函数，仅供检测用
{
	timer0IntCount++;
	if(timer0IntCount==4000)
	{
		timer0IntCount=0;
		second++;
		if(second==60)
		{
			second=0;
			minute++;
			if(minute==60)
			{
				minute=0;
				hour++;
				if(hour==24)
				{
					hour=0;
					day++;
				}
			}
		}
	}
}
#endif

void TIMER_0() interrupt 1//定时器0中断入口，负责产生PWM波
{
	__PWMControl();	
}