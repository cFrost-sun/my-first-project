/*--------------------------------------------------------------------------
PCF8591.c

Code file for PCF8591.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/

#include"PCF8591.h"

UINT_8 ReadADC(UINT_8 Channel)
{
	UINT_8 value;
	I2CStart();               //启动总线
	if(!I2CSendByte(AddWrite))return(64);//发送器件地址
	if(!I2CSendByte(0x40|Channel))return(128);//发送器件子地址
	I2CStart();
	if(!I2CSendByte(AddRead))return(192);
	value=I2CReceiveByte();
	I2CNoAck();                 //发送非应位
	I2CStop();                  //结束总线
	return value;
}
/*BOOL WriteDAC(UINT_8 dat)
{
	dat--;
	return 0;
}*/

