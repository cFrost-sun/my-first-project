/*--------------------------------------------------------------------------
PWM.H

Header file for generic 80C51 and 80C31 microcontroller, put out PWM waves with P0^4~7, use Timer0.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#include<reg51.h>
#include"Define.h"

/*定义PWM输出端口*/
sbit PWM0=P0^7;
sbit PWM1=P0^6;
sbit PWM2=P0^5;
sbit PWM3=P0^4;

void PWMInit();	//PWM初始化函数，使用定时器0
