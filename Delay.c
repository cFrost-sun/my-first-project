/*--------------------------------------------------------------------------
DEALY.C

Code file for generic 80C51 and 80C31 microcontroller.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#include"Delay.h"

void Delay(UINT_16 ms)
{
	while(ms--)
	{
		UINT_8 i=100;
		while(i--);
	}
}