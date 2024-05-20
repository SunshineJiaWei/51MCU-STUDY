#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

//蜂鸣器端口定义
sbit Buzzer = P2^5;

//播放速度，值为四分音符的时长(ms)
#define SPEED	500

//音符与索引对应表，P：休止符，L：低音，M：中音，H：高音，下划线：升半音符号#
enum NOTE
{
	P_=0,
	L1,L1_,L2,L2_,L3,L4,L4_,L5,L5_,L6,L6_,L7,
	M1,M1_,M2,M2_,M3,M4,M4_,M5,M5_,M6,M6_,M7,
	H1,H1_,H2,H2_,H3,H4,H4_,H5,H5_,H6,H6_,H7
};

//索引与频率对照表
unsigned int FreqTable[] = {
	0,
	63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64524, // 低音
	64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030, // 中音
	65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283  // 高音
};

// 乐谱
// 天空之城
// 变量名前加入code关键字，将其存储在ROM(Flash)中，只可读不可写
unsigned char code Music[] = {
	//音符,时值,
	//1
	P_,	4,
	P_,	4,
	P_,	4,
	M6,	2,
	M7,	2,
	
	H1,	4+2,
	M7,	2,
	H1,	4,
	H3,	4,
	
	M7,	4+4+4,
	M3,	2,
	M3,	2,
	
	//2
	M6,	4+2,
	M5,	2,
	M6, 4,
	H1,	4,
	
	M5,	4+4+4,
	M3,	4,
	
	M4,	4+2,
	M3,	2,
	M4,	4,
	H1,	4,
	
	//3
	M3,	4+4,
	P_,	2,
	H1,	2,
	H1,	2,
	H1,	2,
	
	M7,	4+2,
	M4_,2,
	M4_,4,
	M7,	4,
	
	M7,	8,
	P_,	4,
	M6,	2,
	M7,	2,
	
	//4
	H1,	4+2,
	M7,	2,
	H1,	4,
	H3,	4,
	
	M7,	4+4+4,
	M3,	2,
	M3,	2,
	
	M6,	4+2,
	M5,	2,
	M6, 4,
	H1,	4,
	
	//5
	M5,	4+4+4,
	M2,	2,
	M3,	2,
	
	M4,	4,
	H1,	2,
	M7,	2+2,
	H1,	2+4,
	
	H2,	2,
	H2,	2,
	H3,	2,
	H1,	2+4+4,
	
	//6
	H1,	2,
	M7,	2,
	M6,	2,
	M6,	2,
	M7,	4,
	M5_,4,
	
	
	M6,	4+4+4,
	H1,	2,
	H2,	2,
	
	H3,	4+2,
	H2,	2,
	H3,	4,
	H5,	4,
	
	//7
	H2,	4+4+4,
	M5,	2,
	M5,	2,
	
	H1,	4+2,
	M7,	2,
	H1,	4,
	H3,	4,
	
	H3,	4+4+4+4,
	
	//8
	M6,	2,
	M7,	2,
	H1,	4,
	M7,	4,
	H2,	2,
	H2,	2,
	
	H1,	4+2,
	M5,	2+4+4,
	
	H4,	4,
	H3,	4,
	H3,	4,
	H1,	4,
	
	//9
	H3,	4+4+4,
	H3,	4,
	
	H6,	4+4,
	H5,	4,
	H5,	4,
	
	H3,	2,
	H2,	2,
	H1,	4+4,
	P_,	2,
	H1,	2,
	
	//10
	H2,	4,
	H1,	2,
	H2,	2,
	H2,	4,
	H5,	4,
	
	H3,	4+4+4,
	H3,	4,
	
	H6,	4+4,
	H5,	4+4,
	
	//11
	H3,	2,
	H2,	2,
	H1,	4+4,
	P_,	2,
	H1,	2,
	
	H2,	4,
	H1,	2,
	H2,	2+4,
	M7,	4,
	
	M6,	4+4+4,
	P_,	4,
	
	0xFF	//停止标志位
};

unsigned char FreqSelect, MusicSelect;

void main()
{
	Timer0Init();
	while(1)
	{
		if(FreqSelect != 0xFF)					//如果不是停止标志位
		{
			FreqSelect = Music[MusicSelect];	//选择音符对应的频率
			MusicSelect++;
			// Delay(SPEED/4 * Music[MusicSelect]) 通过阻塞程序执行来控制音符的持续时间。
			//在延迟期间，定时器中断会继续切换蜂鸣器的状态，维持音符的播放。延迟时间长短决定了每个音符的播放时长，从而形成一首乐曲
			Delay(SPEED/4*Music[MusicSelect]);	//选择音符对应的时值
			MusicSelect++;
			TR0 = 0;
			Delay(5);							//音符间短暂停顿
			TR0 = 1;
		}
		else									//如果是停止标志位
		{
			//重新播放音乐
			MusicSelect = 0;	
			FreqSelect = 0;				
		}
		
	}
}

void Timer0_Routine() interrupt 1 
{
	// 周期越短，频率越高
	//取对应频率值的重装载值到定时器
	if(FreqTable[FreqSelect])					//如果不是休止符
	{
		TL0 = FreqTable[FreqSelect] % 256;		//设置定时初值
		TH0 = FreqTable[FreqSelect] / 256;		//设置定时初值
		Buzzer = !Buzzer;						//翻转蜂鸣器IO口
	}
}

