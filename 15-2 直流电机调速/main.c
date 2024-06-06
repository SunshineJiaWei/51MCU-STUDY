#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "NixieTube.h"
#include "Timer0.h"

// 引脚定义
sbit Motor = P1^0;

// 计数器，比较值
unsigned char Counter, Compare;
// 按键值，速度挡位
unsigned char KeyNum, Speed;


void main()
{
	Timer0_Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum == 1)
		{
			// 三档调速，根据挡位来调节比较值，从而控制电机速度
			Speed++;
			Speed %= 4;
			if(Speed == 0){Compare = 0;} 
			if(Speed == 1){Compare = 50;} 
			if(Speed == 2){Compare = 75;} 
			if(Speed == 3){Compare = 100;} 
		}
		NixieTube(1, Speed); // 数码管显示挡位
}

void Timer0_Routine() interrupt 1
{
	TL0 = 0xAE;			//设置定时初值
	TH0 = 0xFB;			//设置定时初值
	Counter++;
	Counter %= 100;
	if(Counter < Compare)
	{
		// 计数器小于比较值时，电机转动
		Motor = 1;
	}
	else 
	{
		// 否则电机停止
		Motor = 0;
	}
}