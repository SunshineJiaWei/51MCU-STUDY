#include <REGX52.H>
#include "Delay.h"

// 引脚定义
sbit OneWire_DQ = P3^7;

/**
	* @brief 	单总线初始化
	* @param	无
	* @retval	从机响应位，0为响应，1为未响应
*/
unsigned char OneWire_Init()
{
	unsigned char i;
	unsigned char AckBit;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	i = 227; while (--i);		//Delay 500us
	OneWire_DQ = 1;
	i = 29;	while (--i);		//Delay 70us
	AckBit = OneWire_DQ;
	i = 227; while (--i);		//Delay 500us
	return AckBit;
}

/**
	* @brief  单总线发送一位
	* @param  Bit 要发送的位
	* @retval 无
*/
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ = 0;
	i = 4; while (--i);			//Delay 10us
	OneWire_DQ = Bit;
	i = 22; while (--i);		//Delay 50us
	OneWire_DQ = 1;
}

/**
	* @brief  单总线接收一位
	* @param  无
	* @retval 读取的位
*/
unsigned char OneWire_ReceiveBit()
{
	unsigned char i;
	unsigned char Bit;
	OneWire_DQ = 0;
	i = 2; while (--i);			//Delay 5us
	OneWire_DQ = 1;
	i = 2; while (--i);			//Delay 5us
	Bit = OneWire_DQ;
	i = 22; while (--i);		//Delay 50us
	return Bit;
}

/**
	* @brief  单总线发送一个字节
	* @param  Byte 要发送的字节
	* @retval 无
*/
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0;i < 8;i++)
	{
		OneWire_SendBit(Byte & (0x01 << i));
	}
}

/**
	* @brief  单总线接收一个字节
	* @param  无
	* @retval 接收的一个字节
*/
unsigned char OneWire_ReceiveByte()
{
	unsigned char i;
	unsigned char Byte = 0x00;
	for(i = 0;i < 8;i++)
	{
		if(OneWire_ReceiveBit())
		{
			Byte |= (0x01 << i);
		}
	}
	return Byte;
}
 