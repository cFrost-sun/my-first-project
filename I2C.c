/*--------------------------------------------------------------------------
I2C.C

Code file for generic 80C51 and 80C31 microcontroller.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#include"I2C.h"

void I2CStart()
{
	I2C_SDA=1;
	DelayNop();
	I2C_SCL=1;
	DelayNop();
	I2C_SDA=0;
	DelayNop();
	I2C_SCL=0;
	DelayNop();
}
void I2CStop()
{
	I2C_SDA=0;
	DelayNop();
	I2C_SCL=1;
	DelayNop();
	I2C_SDA=1;
	DelayNop();
	I2C_SCL=0;
}
BOOL I2CSendByte(UINT_8 dat)//发送字节函数，返回值代表是否发送成功
{
	UINT_8 i;
	BOOL result;
	for(i=0;i<8;i++)  //要传送的数据长度为8位
	{
	if((dat<<i)&0x80)//判断发送位
		I2C_SDA=1;   
	else
		I2C_SDA=0;                
	_nop_();
	I2C_SCL=1;               //置时钟线为高，通知被控器开始接收数据位
	DelayNop();//保证时钟高电平周期大于4μ
	I2C_SCL=0; 
	}
	DelayNop();
	I2C_SDA=1;               //8位发送完后释放数据线，准备接收应答位
	DelayNop();  
    I2C_SCL=1;
	DelayNop();
    if(I2C_SDA==1)//判断是否接收到应答信号
		result=0;
	else
		result=1;
    I2C_SCL=0;
	return result;
}
UINT_8 I2CReceiveByte(void)//接受字节函数
{
	UINT_8 i,dat;
 	dat=0; 
	I2C_SDA=1;             //置数据线为输入方式
	for(i=0;i<8;i++)
	{          
		I2C_SCL=0;//置时钟线为低，准备接收数据位
		DelayNop();//时钟低电平周期大于4.7us
		I2C_SCL=1;//置时钟线为高使数据线上数据有效
		DelayNop();
		dat<<=1;
        if(I2C_SDA==1)
		{
			dat++; //读数据位,接收的数据位放入参数中
		}
	}
	I2C_SCL=0;
	return dat;
}
/*void I2CAck()
{  
	I2C_SDA=0;
	DelayNop();     
	I2C_SCL=1;
	DelayNop();//时钟低电平周期大于4μ  
	I2C_SCL=0;   
}*/
void I2CNoAck()
{  
	I2C_SDA=1;
	DelayNop();     
	I2C_SCL=1;
	DelayNop(); //时钟低电平周期大于4μ  
	I2C_SCL=0;   
}