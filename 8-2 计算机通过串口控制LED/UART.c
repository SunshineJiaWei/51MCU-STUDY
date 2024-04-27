#include <REGX52.H>

/**
	* @brief	串口初始化，4800bps, 11.0592MHz
	* @param	无
	* @retval	无
*/
void UART_Init() 	//4800bps@11.0592MHz
{
	SCON = 0x50;
	PCON &= 0x7F;
	// 8位自动重装载定时器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	ES = 1;
	EA = 1;
	PS = 0;

}

/**
	* @brief	串口发送一个字节数据
	* @param	无
	* @retval	无
*/
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(TI == 0);
	TI = 0; 
}

/* 串口中断函数模板
void UART_Routine() interrupt 4
{
	if(RI == 1)
	{
		RI = 0;
	}
}
	
*/