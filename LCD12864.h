/*--------------------------------------------------------------------------
LCD12864.H

Header file for Lcd12864 with ST7920.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __LCD12864_H__
#define __LCD12864_H__

#include<reg51.h>
#include"Define.h"
#include"Delay.h"

/*串并口选择宏*/
//#define __P_PORT__
#define __S_PORT__

void LcdInit();	//显示器初始化,参数0代表串口模式,1代表并口模式
void LcdPrintStr(UCHAR_8 *,UINT_8,UINT_8);//任意位置写字符串
void LcdPrintPic(UCHAR_8 *);//绘图
void LcdClear();//清除LCD的显示内容

#ifdef __P_PORT__/*并口_BEGIN*/
#define LCD_data P0//数据口
sbit LCD_RS=P1^0; //寄存器选择输入 
sbit LCD_RW=P1^1; //液晶读/写控制
sbit LCD_EN=P2^5; //液晶使能控制
#endif/*并口_END*/

#ifdef __S_PORT__/*串口_BEGIN*/
sbit LCD_CS=P1^0; //液晶使能控制 
sbit LCD_SID=P1^3; //液晶数据线
sbit LCD_SCLK=P1^2; //液晶时钟


#define LCD_ENABLE LCD_CS=1
#define LCD_DISABLE LCD_CS=0
#endif/*串口_END*/

#endif