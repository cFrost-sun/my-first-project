/*--------------------------------------------------------------------------
UI.H

Header file for generic 80C51 and 80C31 microcontroller, need LCD12864.h & SmokeDetector.h.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __UI_H__
#define __UI_H__

#include"Define.h"
#include"Delay.h"
#include"LCD12864.h"
#include"KeyBoard16.h"
#include"SmokeDetector.h"
#include"ScrSmokeCode.h"
#include"ScrSetup.h"

void UiInit();//UI初始化
void UiMain();//UI主屏幕
#endif