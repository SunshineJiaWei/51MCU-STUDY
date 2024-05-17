#include <REGX52.H>

// 引脚定义
sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

// 寄存器写入地址定义
#define DS1302_SECOND	0x80
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84
#define DS1302_DATE		0x86
#define DS1302_MONTH	0x88
#define DS1302_DAY		0x8A
#define DS1302_YEAR		0x8C
#define DS1302_WP		0x8E

// 时间数据：年、月、日、时、分、秒、星期
unsigned char DS1302_Time[] = {24,1,1,23,59,55,1};

/**
	* @brief 	DS1302初始化
	* @param	无
	* @retval	无
*/
void DS1302_Init()
{
	DS1302_SCLK = 0;
	DS1302_IO = 0;
}

/**
	* @brief 	DS1302写入一个字节
	* @param	Command：写入的命令字段
	* @param	Data：写入的数据
	* @retval	无
*/
void DS1302_WriteByte(unsigned char Command, Data)
{
	unsigned char i;
	DS1302_CE = 1;
	  
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = Data & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	DS1302_CE = 0;
}

/**
	* @brief 	DS1302读取一个字节
	* @param	Command：写入的命令字段
	* @retval	读出的数据
*/
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i, Data = 0x00;
	Command |= 0x01; // 将写指令变成读指令，最低为置1
	DS1302_CE = 1;
	
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	
	for(i = 0;i < 8;i++)
	{
		DS1302_SCLK  = 1;
		DS1302_SCLK = 0;
		// 读：IO口读取Data字节数据，一位一位读，若此时为1，则将对应位的Data的值置1
		if(DS1302_IO){Data |= (0x01 << i);}
	}
	
	DS1302_CE = 0;
	//读取后将IO设置为0，否则读出的数据会出错
	DS1302_IO = 0;	
	return Data;
}

/**
	* @brief 	BCD编码转成十进制数
	* @param	BCD：需要转换的BCD编码
	* @retval	BCD的十进制数
*/
unsigned char BCD_TO_DEC(unsigned char BCD)
{
	unsigned char DEC = BCD / 16 * 10 + BCD % 16;
	return DEC;
}

/**
	* @brief 	十进制转换成BCD编码
	* @param	DEC：需要转换的十进制数
	* @retval	十进制数的BCD编码
*/
unsigned char DEC_TO_BCD(unsigned char DEC)
{
	unsigned char BCD = DEC / 10 * 16 + DEC % 10;
	return BCD;
}

/**
	* @brief 	DS1302设置时间，函数调用后，DS1302_Time数组中的值会写入到DS1302中
	* @param	无
	* @retval	无
*/
void DS1302_SetTime()
{
	// 关闭写保护
	DS1302_WriteByte(DS1302_WP,0x80); 
	DS1302_WriteByte(DS1302_YEAR,DEC_TO_BCD(DS1302_Time[0]));
	DS1302_WriteByte(DS1302_MONTH,DEC_TO_BCD(DS1302_Time[1]));
	DS1302_WriteByte(DS1302_DATE,DEC_TO_BCD(DS1302_Time[2]));
	DS1302_WriteByte(DS1302_HOUR,DEC_TO_BCD(DS1302_Time[3]));
	DS1302_WriteByte(DS1302_MINUTE,DEC_TO_BCD(DS1302_Time[4]));
	DS1302_WriteByte(DS1302_SECOND,DEC_TO_BCD(DS1302_Time[5]));
	DS1302_WriteByte(DS1302_DAY,DEC_TO_BCD(DS1302_Time[6]));
	//  打开写保护
	DS1302_WriteByte(DS1302_WP,0x00);
}

/**
	* @brief 	DS1302读取时间，函数调用后，读取到的BCD编码值后转换成十进制数存入时间数组中
	* @param	无
	* @retval	无
*/
void DS1302_ReadTime()
{
	DS1302_Time[0] = BCD_TO_DEC(DS1302_ReadByte(DS1302_YEAR));
	DS1302_Time[1] = BCD_TO_DEC(DS1302_ReadByte(DS1302_MONTH));
	DS1302_Time[2] = BCD_TO_DEC(DS1302_ReadByte(DS1302_DATE));
	DS1302_Time[3] = BCD_TO_DEC(DS1302_ReadByte(DS1302_HOUR));
	DS1302_Time[4] = BCD_TO_DEC(DS1302_ReadByte(DS1302_MINUTE));
	DS1302_Time[5] = BCD_TO_DEC(DS1302_ReadByte(DS1302_SECOND));
	DS1302_Time[6] = BCD_TO_DEC(DS1302_ReadByte(DS1302_DAY));
}
