/*--------------------------------------------------------------------------
KEYBOARD16.C

Code file for generic 80C51 and 80C31 microcontroller, use Int 0.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#include"KeyBoard16.h"

BOOL msgProced;
UINT_8 msg;

static void __KeyBoardScan();//键盘扫描函数，只能由外部中断0调用

void KeyBoardInit()
{
	msgProced=TRUE;
	msg=0x00;
	IT0=1;//下降沿出发
	EA=1;//开总中断
	EX0=1;//开外部中断0	
	P2=0x0f;	
}

static void __KeyBoardScan()//键盘扫描函数，只能由外部中断0调用！！
{
	UINT_8 i,delayCount;
	
	if(!msgProced)
	{
		return;
	}
	/*这里本想做成真正的消息循环，但单片机的处理能力不够。巧合的
	是，msgProced变量的存在直接有效地解决了按键抖动的问题，	只有
	在前一次中断产生的消息被msgProce()函数响应之后才能进入下个中
	断，响应前的中断无论是否是真实按键按下，都不响应*/

	for(i=1;i<5;i++)
	{
		P2 = (B01111111<<i)|(B01111111>>(8-i));//向左循环移位
		
		delayCount=100;//延时，等待电平稳定
		while(delayCount--);
    
		switch(P2 & B11110000)
		{
			case B11100000: msg=(i<<4)+1;goto RESUCCESS;
			case B11010000: msg=(i<<4)+2;goto RESUCCESS;
			case B10110000: msg=(i<<4)+3;goto RESUCCESS;
			case B01110000: msg=(i<<4)+4;goto RESUCCESS;
			default:msg=0x00;if(i>=4){goto REFAIL;}break;
		} 
		continue;
	}
	
	//TODO:在这里添加部中断0(键盘)的代码
	/*本函数使用了goto语句，我认为这里用goto会使代码变得更加
	简洁易懂，更适合需要尽可能减少指令数量的中断函数*/
	RESUCCESS:
		msgProced = FALSE;
	REFAIL:	
		P2=0x0f;
		return;
}

void INT_0() interrupt 0//键盘中断入口
{
	__KeyBoardScan();	
}
