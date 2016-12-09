/*--------------------------------------------------------------------------
PCF8591.H

Header file for PCF8591, need I2C.h.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __PCF8591_H__
#define __PCF8591_H__

#include"Define.h"
#include"I2C.h"

#define AddWrite 0x90   //写数据地址 
#define AddRead 0x91   //读数据地址

UINT_8 ReadADC(UINT_8);
//BOOL WriteDAC(UINT_8);

#endif