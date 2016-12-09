/*--------------------------------------------------------------------------
SCRSETUP.C

Code file for generic 80C51 and 80C31 microcontroller.
Copyright (c) cFrost.
All rights reserved.
--------------------------------------------------------------------------*/
#include"ScrSetup.h"

/*消息处理相关变量，在KeyBoard16.h中定义*/
extern BOOL msgProced;
extern UINT_8 msg;

/*PWM占空比控制参数，目前提供四档变化，在PWM中定义*/
extern UINT_8 PWM0C;
extern UINT_8 PWM1C;
extern UINT_8 PWM2C;
extern UINT_8 PWM3C;


/*各传感器参数，在SmokeDetector中定义*/
extern struct MODE Detector[4];

extern UINT_8 handle;//句柄，在UI中定义

UINT_8 selectedDetector=0;//用来标记当前选定的传感器

static UINT_8 tempNum=0;//用来临时存储数据
static BOOL someChange=FALSE;//用标记是否有参数改变

static UINT_8 selectedLine=0;//静态变量，每个界面文件都有一个，互相独立

static void setNum(UINT_8);

static void BtnNum0_Clicked();
static void BtnNum1_Clicked();
static void BtnNum2_Clicked();
static void BtnNum3_Clicked();
static void BtnNum4_Clicked();
static void BtnNum5_Clicked();
static void BtnNum6_Clicked();
static void BtnNum7_Clicked();
static void BtnNum8_Clicked();
static void BtnNum9_Clicked();
static void BtnUp_Clicked();
static void BtnDown_Clicked();
//static void BtnLeft_Clicked();
//static void BtnRight_Clicked();
static void BtnOK_Clicked();
static void BtnCancel_Clicked();

void ScrSetup()
{
	switch(msg)
	{
		case BTN_NUM0_DOWN: BtnNum0_Clicked();break;
		case BTN_NUM1_DOWN: BtnNum1_Clicked();break;
		case BTN_NUM2_DOWN: BtnNum2_Clicked();break;
		case BTN_NUM3_DOWN: BtnNum3_Clicked();break;
		case BTN_NUM4_DOWN: BtnNum4_Clicked();break;
		case BTN_NUM5_DOWN: BtnNum5_Clicked();break;
		case BTN_NUM6_DOWN: BtnNum6_Clicked();break;
		case BTN_NUM7_DOWN: BtnNum7_Clicked();break;
		case BTN_NUM8_DOWN: BtnNum8_Clicked();break;
		case BTN_NUM9_DOWN: BtnNum9_Clicked();break;
		case BTN_UP_DOWN: BtnUp_Clicked();break;
		case BTN_DOWN_DOWN: BtnDown_Clicked();break;
		//case BTN_LEFT_DOWN: BtnLeft_Clicked();break;
		//case BTN_RIGHT_DOWN: BtnRight_Clicked();break;
		case BTN_OK_DOWN: BtnOK_Clicked();break;
		case BTN_CANCEL_DOWN: BtnCancel_Clicked();break;
		default:msg=0x00;break;
	}
}

void PrintSetup()
{
	UCHAR_8 temp[16];
	
	if(!someChange)
	{
		sprintf(temp,"报警时间:%3d秒",(INT_16)Detector[selectedDetector].warningTime);
		LcdPrintStr(temp,0,1);
		sprintf(temp,"间隔时间:%3d秒",(INT_16)Detector[selectedDetector].sleepTime);
		LcdPrintStr(temp,1,1);
		sprintf(temp,"报警浓度:%3d%% ",(INT_16)Detector[selectedDetector].enableConcentration);
		LcdPrintStr(temp,2,1);
		sprintf(temp,"间隔时间:%3d%% ",(INT_16)Detector[selectedDetector].fanStartConcentration);
		LcdPrintStr(temp,3,1);
	}
	else
	{
		LcdPrintStr("报警时间",0,1);
		LcdPrintStr("间隔时间",1,1);
		LcdPrintStr("报警浓度",2,1);  
		LcdPrintStr("间隔时间",3,1);
		LcdPrintStr("秒",0,7);
		LcdPrintStr("秒",1,7);
		LcdPrintStr("% ",2,7);  
		LcdPrintStr("% ",3,7);
		if(selectedLine==0)
		{
			sprintf(temp,":%3d",(INT_16)tempNum);
			LcdPrintStr(temp,0,5);
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].sleepTime);
			LcdPrintStr(temp,1,5);
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].enableConcentration);
			LcdPrintStr(temp,2,5);
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].fanStartConcentration);
			LcdPrintStr(temp,3,5);	
		}
		else if(selectedLine==1)
		{
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].warningTime);
			LcdPrintStr(temp,0,5);
			sprintf(temp,":%3d",(INT_16)tempNum);
			LcdPrintStr(temp,1,5);
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].enableConcentration);
			LcdPrintStr(temp,2,5);
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].fanStartConcentration);
			LcdPrintStr(temp,3,5);	
		}
		else if(selectedLine==2)
		{
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].warningTime);
			LcdPrintStr(temp,0,5);
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].sleepTime);
			LcdPrintStr(temp,1,5);
			sprintf(temp,":%3d",(INT_16)tempNum);
			LcdPrintStr(temp,2,5);
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].fanStartConcentration);
			LcdPrintStr(temp,3,5);	
		}
		else if(selectedLine==3)
		{
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].warningTime);
			LcdPrintStr(temp,0,5);
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].sleepTime);
			LcdPrintStr(temp,1,5);
			sprintf(temp,":%3d",(INT_16)Detector[selectedDetector].enableConcentration);
			LcdPrintStr(temp,2,5);
			sprintf(temp,":%3d",(INT_16)tempNum);
			LcdPrintStr(temp,3,5);	
		}
	}
	
	LcdPrintStr(">>",selectedLine,0);
	if(selectedLine>0)LcdPrintStr("  ",selectedLine-1,0);
	if(selectedLine>1)LcdPrintStr("  ",selectedLine-2,0);
	if(selectedLine>2)LcdPrintStr("  ",selectedLine-3,0);
	if(selectedLine<3)LcdPrintStr("  ",selectedLine+1,0);
	if(selectedLine<2)LcdPrintStr("  ",selectedLine+2,0);
	if(selectedLine<1)LcdPrintStr("  ",selectedLine+3,0);
}

static void BtnNum0_Clicked()
{
	setNum(0);
	////TODO:在这里添加按键0按下时的处理语句 	
}
static void BtnNum1_Clicked()
{
	setNum(1);
	////TODO:在这里添加按键1按下时的处理语句 	
}
static void BtnNum2_Clicked()
{
	setNum(2);
	////TODO:在这里添加按键2按下时的处理语句 	
}
static void BtnNum3_Clicked()
{
	setNum(3);
	////TODO:在这里添加按键3按下时的处理语句 	
}
static void BtnNum4_Clicked()
{
	setNum(4);
	////TODO:在这里添加按键4按下时的处理语句 	
}
static void BtnNum5_Clicked()
{
	setNum(5);
	////TODO:在这里添加按键5按下时的处理语句 	
}
static void BtnNum6_Clicked()
{
	setNum(6);
	////TODO:在这里添加按键6按下时的处理语句 	
}
static void BtnNum7_Clicked()
{
	setNum(7);
	////TODO:在这里添加按键7按下时的处理语句 	
}
static void BtnNum8_Clicked()
{
	setNum(8);
	////TODO:在这里添加按键8按下时的处理语句 	
}
static void BtnNum9_Clicked()
{
	setNum(9);
	////TODO:在这里添加按键9按下时的处理语句 	
}
static void BtnUp_Clicked()
{
	tempNum=0;
	someChange=FALSE;
	selectedLine--;
	if(selectedLine<0||selectedLine>3) {selectedLine=3;}
	////TODO:在这里添加按键上按下时的处理语句
}
static void BtnDown_Clicked()
{
	tempNum=0;
	someChange=FALSE;
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
	if(someChange)
	{
		switch(selectedLine)
		{
			case 0:Detector[selectedDetector].warningTime=tempNum;break;
			case 1:Detector[selectedDetector].sleepTime=tempNum;break;
			case 2:Detector[selectedDetector].enableConcentration=tempNum;break;
			case 3:Detector[selectedDetector].fanStartConcentration=tempNum;break;
		}
		
		tempNum=0;
		someChange=FALSE;
	}
	selectedLine++;
	if(selectedLine>3) 
	{
		tempNum=0;
		someChange=FALSE;
		selectedLine=0;
		handle=SCR_SMOKECODE;
	}
	////TODO:在这里添加按键确认按下时的处理语句
}	 
static void BtnCancel_Clicked()
{
	tempNum=0;
	someChange=FALSE;
	selectedLine=0;
	handle=SCR_SMOKECODE;
	////TODO:在这里添加按键取消按下时的处理语句
}

void setNum(UINT_8 key)
{
	someChange=TRUE;
	if((int)tempNum*10+key>255 && selectedLine<2)//只有前两个属性最大值为255，其余为100
	{
		tempNum=255;
	}
	else if((int)tempNum*10+key>100 && selectedLine>1)
	{
		tempNum=100;
	}
	else
	{
		tempNum=tempNum*10+key;
	}
}