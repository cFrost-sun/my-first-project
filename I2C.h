/*--------------------------------------------------------------------------
I2C.H

Header file for generic 80C51 and 80C31 microcontroller.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#include<reg51.h>
#include"Define.h"
#include"Delay.h"

sbit I2C_SCL=P3^0;//定义I2C时钟线
sbit I2C_SDA=P3^1;//定义I2C数据线

void I2CStart();
void I2CStop();
BOOL I2CSendByte(UINT_8);//发送字节函数，返回值代表是否发送成功
UINT_8 I2CReceiveByte();//接受字节函数
//void I2CAck();//应答函数
void I2CNoAck();//非应答函数
#endif