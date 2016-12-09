/*--------------------------------------------------------------------------
LCD12864.C

Code file for Lcd12864 with ST7920.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#include"LCD12864.h"

static void __Lcd_SetPoint(UINT_8,UINT_8);//设定显示位置

#ifdef __P_PORT__/*并口_BEGIN*/
static void __Lcd_CheckBusy(); //检查显示器忙
static void __Lcd_WriteCMD(UINT_8); //写指令
static void __Lcd_WriteData(UINT_8); //写数据
#endif/*并口_END*/

#ifdef __S_PORT__/*串口_BEGIN*/
static void __Lcd_SendByte(UINT_8);//送出一个字节
static UINT_8 __Lcd_ReceiveByte();//接受一个字节
static void __Lcd_CheckBusy(); //检查显示器忙
static void __Lcd_WriteCMD(UINT_8); //写指令
static void __Lcd_WriteData(UINT_8); //写数据
#endif/*串口_END*/

static void __Lcd_SetPoint(UINT_8 line,UINT_8 row)//设定显示位置
{
	UINT_8 pos;
	if (line==0)
		{line=0x80;}
	else if (line==1)
		{line=0x90;}
	else if (line==2)
		{line=0x88;}
	else if (line==3)
		{line=0x98;}
	pos = line+row ;  
	__Lcd_WriteCMD(pos);     //显示地址
}

void LcdInit()//显示器初始化
{    
    __Lcd_WriteCMD(0x34);      //扩充指令操作
    Delay(5);
    __Lcd_WriteCMD(0x30);      //基本指令操作
    Delay(5);
    __Lcd_WriteCMD(0x0C);      //显示开，关光标
    Delay(5);
    __Lcd_WriteCMD(0x01);      //清除LCD的显示内容
    Delay(5);
}

void LcdClear()//清除LCD的显示内容
{
    __Lcd_WriteCMD(0x01);	
}

void LcdPrintStr(UCHAR_8 * str, UINT_8 line, UINT_8 row)//任意位置写字符串
{
	UINT_8 i;
	__Lcd_SetPoint(line,row);
    i = 0;
    while(str[i] != '\0' && i<(16-(row<<1)))//如果字符串结束且未进入下一行,row*2是因为一列占2个字符
    {
		__Lcd_WriteData(str[i]);
		i++;
    }
}

void LcdPrintPic(UCHAR_8 *ptr)
{
	UCHAR_8 i,j,k; 
	__Lcd_WriteCMD(0x34);        //打开扩展指令集
	i = 0x80;            
	for(j = 0;j < 32;j++)
	{
        __Lcd_WriteCMD(i++);
        __Lcd_WriteCMD(0x80);
  		for(k = 0;k < 16;k++)
  		{
  		    __Lcd_WriteData(*ptr++);
  		}
	}
	i = 0x80;
 	for(j = 0;j < 32;j++)
	{
 	    __Lcd_WriteCMD(i++);
        __Lcd_WriteCMD(0x88);	   
  		for(k = 0;k < 16;k++)
  		{
   		    __Lcd_WriteData(*ptr++);
   		} 
	}  
    __Lcd_WriteCMD(0x36);        //打开绘图显示
	__Lcd_WriteCMD(0x30);        //回到基本指令集
}

#ifdef __P_PORT__/*并口程序_BEGIN*/
static void __Lcd_CheckBusy() //检查显示器忙
{
	bit result;
	do
	{
		LCD_RS = 0;
    	LCD_RW = 1;
    	LCD_EN = 1;
    	DelayNop();
    	result = (bit)(P0&0x80);
    	LCD_EN = 0;
	}while(result);
}
static void __Lcd_WriteCMD(UCHAR_8 cmd) //写指令
{
	__Lcd_CheckBusy();
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    DealyNop(); 
    P0 = cmd;
    DealyNop();
    LCD_EN = 1;
    DealyNop();
    LCD_EN = 0; 
}
static void __Lcd_WriteData(UCHAR_8 dat)//写数据
{                          
	__Lcd_CheckBusy();
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    DealyNop();
    LCD_EN = 1;
    DealyNop();
    LCD_EN = 0; 
}
#endif/*并口程序_END*/

#ifdef __S_PORT__/*串口程序_BEGIN*/
static void __Lcd_SendByte(UINT_8 dat)//送出一个字节
{
	UINT_8 i;
	LCD_SCLK=0;
	for(i=0;i<8;i++)
	{
		if(dat&0x80)
		{
			LCD_SID=1;
		}
		else
		{
			LCD_SID=0;
		}
		LCD_SCLK=1;
		dat<<=1;
		LCD_SCLK=0;
	}
}
static UINT_8 __Lcd_ReceiveByte()//接受一个字节
{
	UINT_8 i,temp1=0,temp2=0;
	LCD_SCLK=0;
	for(i=0;i<8;i++)
	{
		temp1<<=1;
		LCD_SCLK=1;
		LCD_SCLK=0;
		if(LCD_SID) temp1++;
	}
	for(i=0;i<8;i++)
	{
		temp2<<=1;
		LCD_SCLK=1;
		LCD_SCLK=0;
		if(LCD_SID) temp2++;
	}
	return ((temp1&0xf0)+(temp2&0x0f));
}
static void __Lcd_CheckBusy() //检查显示器忙
{
	do
	{
		__Lcd_SendByte(0xfc); //11111RW(1)RS(0)0
	}while(__Lcd_ReceiveByte()&0x80);
}
static void __Lcd_WriteCMD(UINT_8 cmd)//写指令
{
	LCD_ENABLE;
	__Lcd_CheckBusy();
	__Lcd_SendByte(0xf8);
	__Lcd_SendByte(cmd&0xf0);
	__Lcd_SendByte((cmd&0x0f)<<4);
	LCD_DISABLE;
}
static void __Lcd_WriteData(UINT_8 dat) //写数据
{
	LCD_ENABLE;
	__Lcd_CheckBusy();
	__Lcd_SendByte(0xfa);
	__Lcd_SendByte(dat&0xf0);
	__Lcd_SendByte((dat&0x0f)<<4);
	LCD_DISABLE;
}
#endif/*串口程序_END*/