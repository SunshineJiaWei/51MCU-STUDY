#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

// 键码值，模式，时间选择标志位，设置时间闪烁标志位
unsigned char KeyNum, MODE, TimeSetSelect, TimeSetFlashFlag;

/**
	* @brief 	从DS1302中读取数据并更新到数组中，通过数组中的值来显示时间
	* @param	无
	* @retval	无
*/
void TimeShow()
{
	DS1302_ReadTime();
	LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);
}

/**
* @brief 	根据键码值选择对应的操作，2：年月日时分秒循环选择、3：根据选择的对应位，实现时间增加、4：根据选择的对应位，实现时间减小
	* @param 	无
	* @retval	无
*/
void ModifyTime()
{
	if(KeyNum == 2)
	{ 
		TimeSetSelect++;
		TimeSetSelect %= 6;
	}
	if(KeyNum == 3)
	{
		DS1302_Time[TimeSetSelect]++;
		if(DS1302_Time[0]>99){DS1302_Time[0] = 0;} // 年
		if(DS1302_Time[1]>12){DS1302_Time[1] = 1;} // 月
		// 日
		if(DS1302_Time[1] == 1 ||
		DS1302_Time[1] == 3 ||
		DS1302_Time[1] == 5 ||
		DS1302_Time[1] == 7 ||
		DS1302_Time[1] == 8 ||
		DS1302_Time[1] == 10||
		DS1302_Time[1] == 12)
		{
			if(DS1302_Time[2]>31){DS1302_Time[2] = 1;}
		}
		else if(
		DS1302_Time[1] == 4 ||
		DS1302_Time[1] == 6 ||
		DS1302_Time[1] == 9 ||
		DS1302_Time[1] == 11)
		{
			if(DS1302_Time[2]>30){DS1302_Time[2] = 1;}
		}
		else if(DS1302_Time[1] == 2)
		{
			if(DS1302_Time[0] % 4 == 0)
			{
				if(DS1302_Time[2]>29){DS1302_Time[2] = 1;}
			}
			else 
			{
				if(DS1302_Time[2]>28){DS1302_Time[2] = 1;}
			}
		}
		if(DS1302_Time[3]>23){DS1302_Time[3] = 0;} // 时
		if(DS1302_Time[4]>59){DS1302_Time[4] = 0;} // 分
		if(DS1302_Time[5]>59){DS1302_Time[5] = 0;} // 秒
	}
	if(KeyNum == 4)
	{
		DS1302_Time[TimeSetSelect]--;
		if(DS1302_Time[0]<0){DS1302_Time[0] = 99;}
		if(DS1302_Time[1]<1){DS1302_Time[1] = 12;}
		if(DS1302_Time[1] == 1 ||
		DS1302_Time[1] == 3 ||
		DS1302_Time[1] == 5 ||
		DS1302_Time[1] == 7 ||
		DS1302_Time[1] == 8 ||
		DS1302_Time[1] == 10||
		DS1302_Time[1] == 12)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2] = 31;}
			if(DS1302_Time[2]>31){DS1302_Time[2] = 1;}
		}
		else if(
		DS1302_Time[1] == 4 ||
		DS1302_Time[1] == 6 ||
		DS1302_Time[1] == 9 ||
		DS1302_Time[1] == 11)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2] = 30;}
			if(DS1302_Time[2]>30){DS1302_Time[2] = 1;}
		}
		else if(DS1302_Time[1] == 2)
		{
			if(DS1302_Time[0] % 4 == 0)
			{
				if(DS1302_Time[2]<1){DS1302_Time[2] = 29;}
				if(DS1302_Time[2]>29){DS1302_Time[2] = 1;}
			}
			else 
			{
				if(DS1302_Time[2]<1){DS1302_Time[2] = 28;}
				if(DS1302_Time[2]>28){DS1302_Time[2] = 1;}
			}
		}
		if(DS1302_Time[3]<0){DS1302_Time[3] = 23;}
		if(DS1302_Time[4]<0){DS1302_Time[4] = 59;}
		if(DS1302_Time[5]<0){DS1302_Time[5] = 59;}
	}
	
	// 当对应位被选中时，且闪烁标志位为1时，闪烁
	if(TimeSetSelect == 0 && TimeSetFlashFlag == 1){LCD_ShowString(1,1,"  ");}
	else {LCD_ShowNum(1,1,DS1302_Time[0],2);}
	
	if(TimeSetSelect == 1 && TimeSetFlashFlag == 1){LCD_ShowString(1,4,"  ");}
	else {LCD_ShowNum(1,4,DS1302_Time[1],2);}
	
	if(TimeSetSelect == 2 && TimeSetFlashFlag == 1){LCD_ShowString(1,7,"  ");}
	else {LCD_ShowNum(1,7,DS1302_Time[2],2);}
	
	if(TimeSetSelect == 3 && TimeSetFlashFlag == 1){LCD_ShowString(2,1,"  ");}
	else {LCD_ShowNum(2,1,DS1302_Time[3],2);}
	
	if(TimeSetSelect == 4 && TimeSetFlashFlag == 1){LCD_ShowString(2,4,"  ");}
	else {LCD_ShowNum(2,4,DS1302_Time[4],2);}
	
	if(TimeSetSelect == 5 && TimeSetFlashFlag == 1){LCD_ShowString(2,7,"  ");}
	else {LCD_ShowNum(2,7,DS1302_Time[5],2);}
}

void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0Init();
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	DS1302_SetTime();
	
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			if(KeyNum == 1)
			{
				if(MODE == 1){MODE = 0;DS1302_SetTime();}
				else if(MODE == 0) {MODE = 1;TimeSetSelect = 0;}
			}
		}
		switch(MODE)
		{
			case 0: TimeShow();break;
			case 1: ModifyTime();break;
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count >= 500)
	{
		T0Count = 0;
		TimeSetFlashFlag = !TimeSetFlashFlag;
	}
	
}