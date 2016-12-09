/*--------------------------------------------------------------------------
DELAY.H

Base delay function file for generic 80C51 and 80C31 microcontroller, Must be included by all header files!
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __DELAY_H__
#define __DELAY_H__

#include<reg51.h>
#include<intrins.h>
#include"Define.h"

#define DelayNop(); {_nop_();_nop_();_nop_();_nop_();_nop_();};
void Delay(UINT_16);

#endif