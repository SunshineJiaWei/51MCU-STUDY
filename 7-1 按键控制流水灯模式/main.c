#include <REGX52.H>
#include <INTRINS.H>
#include "Timer.h"
#include "Key.h"


// 自己配置
//void Timer0_Init()
//{
//	//TMOD = 0x01; // 模式寄存器
//	TMOD &= 0xF0; // 把TMOD的低四位清零，高四位保持不变
//	TMOD |= 0x01; // 把TMOD的最低位置1，高四位保持不变
//	// 控制寄存器
//	TF0 = 0;
//	TR0 = 1;
//	TH0 = 64535 / 256;
//	TL0 = 64535 % 256;
//	// 中断系统
//	ET0 = 1;
//	EA = 1;
//	PT0 = 0;
//}

unsigned char KeyNum, LEDMode;
void main()
{
	P2 = 0xFE;
	//Timer0_Init();
	Timer0Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			if(KeyNum == 1)
			{
				// LEDMode：范围0-1，控制LED灯向左或向右流水灯
				LEDMode++;
				if(LEDMode >= 2) LEDMode = 0;
			}
			
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
		if(LEDMode == 0) P2 = _crol_(P2,1); // 库函数，循环左移
		if(LEDMode == 1) P2 = _cror_(P2,1); // 库函数，循环右移
	}
}
