/*--------------------------------------------------------------------------
SCRSOMKECODE.C

Code file for generic 80C51 and 80C31 microcontroller.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#include"ScrSmokeCode.h"

extern float smokeCode[4];//用来存储四个传感器探测到的烟雾浓度，在SmokeDetector中定义

/*消息处理相关变量，在KeyBoard16.h中定义*/
extern BOOL msgProced;
extern UINT_8 msg;

extern UINT_8 handle;//句柄,在UI中定义

extern UINT_8 selectedDetector;//用来标记当前选定的传感器,在ScrSetup中定义

static UINT_8 selectedLine=0;//静态变量，每个界面文件都有一个，互相独立

//static void BtnNum0_Clicked();
//static void BtnNum1_Clicked();
//static void BtnNum2_Clicked();
//static void BtnNum3_Clicked();
//static void BtnNum4_Clicked();
//static void BtnNum5_Clicked();
//static void BtnNum6_Clicked();
//static void BtnNum7_Clicked();
//static void BtnNum8_Clicked();
//static void BtnNum9_Clicked();
static void BtnUp_Clicked();
static void BtnDown_Clicked();
//static void BtnLeft_Clicked();
//static void BtnRight_Clicked();
static void BtnOK_Clicked();
//static void BtnCancel_Clicked();

void ScrSmokeCode()
{
	switch(msg)
	{
		//case BTN_NUM0_DOWN: BtnNum0_Clicked();break;
		//case BTN_NUM1_DOWN: BtnNum1_Clicked();break;
		//case BTN_NUM2_DOWN: BtnNum2_Clicked();break;
		//case BTN_NUM3_DOWN: BtnNum3_Clicked();break;
		//case BTN_NUM4_DOWN: BtnNum4_Clicked();break;
		//case BTN_NUM5_DOWN: BtnNum5_Clicked();break;
		//case BTN_NUM6_DOWN: BtnNum6_Clicked();break;
		//case BTN_NUM7_DOWN: BtnNum7_Clicked();break;
		//case BTN_NUM8_DOWN: BtnNum8_Clicked();break;
		//case BTN_NUM9_DOWN: BtnNum9_Clicked();break;
		case BTN_UP_DOWN: BtnUp_Clicked();break;
		case BTN_DOWN_DOWN: BtnDown_Clicked();break;
		//case BTN_LEFT_DOWN: BtnLeft_Clicked();break;
		//case BTN_RIGHT_DOWN: BtnRight_Clicked();break;
		case BTN_OK_DOWN: BtnOK_Clicked();break;
		//case BTN_CANCEL_DOWN: BtnCancel_Clicked();break;
		default:msg=0x00;break;
	}
}

void PrintSmokeCode()
{
	UCHAR_8 temp[16];
	UINT_8 i;

	for(i=0;i<4;i++)
	{
		sprintf(temp,"传感器#%d %3.1f%% ",(INT_16)i,smokeCode[i]);//格式输出浓度
		LcdPrintStr(temp,i,1);
	}

	LcdPrintStr(">>",selectedLine,0);
	if(selectedLine>0)LcdPrintStr("  ",selectedLine-1,0);
	if(selectedLine>1)LcdPrintStr("  ",selectedLine-2,0);
	if(selectedLine>2)LcdPrintStr("  ",selectedLine-3,0);
	if(selectedLine<3)LcdPrintStr("  ",selectedLine+1,0);
	if(selectedLine<2)LcdPrintStr("  ",selectedLine+2,0);
	if(selectedLine<1)LcdPrintStr("  ",selectedLine+3,0);
}

/*static void BtnNum0_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键0按下时的处理语句 	
}
static void BtnNum1_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键1按下时的处理语句
}
static void BtnNum2_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键2按下时的处理语句
}
static void BtnNum3_Clicked()
{					  
	selectedLine=4;
	////TODO:在这里添加按键3按下时的处理语句
}
static void BtnNum4_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键4按下时的处理语句
}
static void BtnNum5_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键5按下时的处理语句
}
static void BtnNum6_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键6按下时的处理语句
}	 
static void BtnNum7_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键7按下时的处理语句
}
static void BtnNum8_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键8按下时的处理语句
}
static void BtnNum9_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键9按下时的处理语句
}*/
static void BtnUp_Clicked()
{
	selectedLine--;
	if(selectedLine<0||selectedLine>3) {selectedLine=3;}
	////TODO:在这里添加按键上按下时的处理语句
}
static void BtnDown_Clicked()
{
	selectedLine++;
	if(selectedLine>3) {selectedLine=0;}
	////TODO:在这里添加按键下按下时的处理语句
}
/*static void BtnLeft_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键左按下时的处理语句
}
static void BtnRight_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键右按下时的处理语句
}*/
static void BtnOK_Clicked()
{
	selectedDetector=selectedLine;
	handle=SCR_SETUP;
	////TODO:在这里添加按键确认按下时的处理语句
}
/*static void BtnCancel_Clicked()
{
	selectedLine=4;
	////TODO:在这里添加按键取消按下时的处理语句
}*/