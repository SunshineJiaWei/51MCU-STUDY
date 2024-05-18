#include <REGX52.H>
#include <INTRINS.H>

// 蜂鸣器端口号
sbit Buzzer = P2^5;

/**
	* @brief 	蜂鸣器私有延时函数，延时500us
	* @param	无
	* @retval	无
*/
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
	* @brief 	蜂鸣器鸣响，频率是1000HZ
	* @param	ms：鸣响的时间
	* @retval	无
*/
void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i = 0;i < ms * 2;i++)
	{
		Buzzer = !Buzzer;
		// 一个周期1ms，频率f = 1 / T = 1 / 1ms = 1000HZ
		Buzzer_Delay500us();
	}
}
