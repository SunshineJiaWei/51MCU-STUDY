#include <REGX52.H>
#include "Key.h"
#include "NixieTube.h"
#include "Timer0.h"
#include "Delay.h"
#include "AT24C02.h"

unsigned char KeyNum;
unsigned char Min,Sec,MiniSec;
unsigned char RunFlag;

void main()
{
	Timer0_Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum == 1)
		{
			RunFlag = !RunFlag; //启动标志位翻转
		}
		if(KeyNum == 2)
		{
			Min = 0;
			Sec = 0;
			MiniSec = 0;
			if(RunFlag) RunFlag = !RunFlag;
		}
		if(KeyNum == 3)
		{
			// 时分秒写入AT24C02
			AT24C02_WriteByte(0,Min);
			Delay(5);
			AT24C02_WriteByte(1,Sec);
			Delay(5);
			AT24C02_WriteByte(2,MiniSec);
			Delay(5);
		}
		if(KeyNum == 4)
		{
			// 从AT24C02中读取时分秒
			Min = AT24C02_ReadByte(0);
			Sec = AT24C02_ReadByte(1);
			MiniSec = AT24C02_ReadByte(2);
		}
		//设置显示数据缓存
		Nieix_SetBuf(1,Min/10);
		Nieix_SetBuf(2,Min%10);
		Nieix_SetBuf(3,11);
		Nieix_SetBuf(4,Sec/10);
		Nieix_SetBuf(5,Sec%10);
		Nieix_SetBuf(6,11);
		Nieix_SetBuf(7,MiniSec/10);
		Nieix_SetBuf(8,MiniSec%10);
	}
}

/**
	* @brief 	秒表驱动函数，在中断函数中调用，调用频率为10ms一次
	* @param	无
	* @retval	无
*/
void Sec_Loop()
{
	if(RunFlag)
	{
		//MiniSec 达到100时（意味着已经过了100次10毫秒，即1秒）
		MiniSec++; 
		if(MiniSec >= 100)
		{
			MiniSec = 0;
			Sec++;
			if(Sec >= 60)
			{
				Sec = 0;
				Min++;
				if(Min >= 60)
				{
					Min = 0;
				}
			}
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count1,T0Count2,T0Count3;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count1++;
	if(T0Count1 >= 20)
	{
		T0Count1 = 0;
		KeyLoop();		//20ms调用一次按键驱动函数
	}
	T0Count2++;
	if(T0Count2 >= 2)
	{
		T0Count2 = 0;
		Nieix_Loop();	//2ms调用一次数码管驱动函数
	}
	T0Count3++;
	if(T0Count3 >= 10)
	{
		T0Count3 = 0;
		Sec_Loop();		//10ms调用一次数秒表驱动函数
	}
}

