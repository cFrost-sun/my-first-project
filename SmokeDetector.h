/*--------------------------------------------------------------------------
SMOKEDETECTOR.H

Header file for generic 80C51 and 80C31 microcontroller.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __SMOKEDETECTOR_H__
#define __SMOKEDETECTOR_H__

#include<reg51.h>
#include"Define.h"
#include"PCF8591.h"
#include"PWM.h"


sbit WARNING0=P0^0;
sbit WARNING1=P0^1;
sbit WARNING2=P0^2;
sbit WARNING3=P0^3;

void SmokeDetectorInit();
void SmokeDetector();
void SetWarning();
void SetPWMxC();
#endif