#include <REGX52.H>

// 引脚定义
sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
	* @brief 	I2C开始
	* @param	无
	* @retval	无
*/
void I2C_Start()
{
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
} 

/**
	* @brief 	I2C停止
	* @param	无
	* @retval	无
*/
void I2C_Stop()
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
} 

/**
	* @brief 	I2C发送一个字节
	* @param	Byte：要发送的字节
	* @retval	无
*/
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i= 0;i<8;i++)
	{
		// 高位在前
		I2C_SDA = Byte & (0x80 >> i);
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}

/**
	* @brief 	I2C接收一个字节
	* @param	无
	* @retval	接收到的一个字节
*/
unsigned char I2C_ReceiveByte()
{
	unsigned char Byte = 0x00, i;
	I2C_SDA = 1; // 主机在接收之前，需要释放SDA
	for(i = 0;i < 8;i++)
	{
		I2C_SCL = 1;
		if(I2C_SDA){Byte |= (0x80 >> i);}
		I2C_SCL = 0;
	}
	return Byte;
}

/**
	* @brief 	I2C发送应答
	* @param	AckBit应答位，0表示应答，1表示非应答
	* @retval	无
*/
void I2C_SendAck(unsigned char AckBit)
{
	
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SCL = 0;
}

/**
	* @brief 	I2C接收应答位
	* @param	无
	* @retval	接收到的应答位，0表示应答，1表示非应答
*/
unsigned char I2C_ReceiveAck()
{
	unsigned char AckBit;
	I2C_SDA = 1; // 释放SDA
	I2C_SCL = 1;
	AckBit = I2C_SDA;
	I2C_SCL = 0;
	return AckBit;
}


