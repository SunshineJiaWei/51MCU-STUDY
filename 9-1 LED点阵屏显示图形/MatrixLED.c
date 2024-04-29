#include <REGX52.H>

/**
	* @brief 	74HC595写入一个字节
	* @param 	Byte 要写入的字节
	* @retval	无
*/ 
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER = Byte & (0x80 >> i);
		SCK = 1;
		SCK=0;
	}
	RCK = 1;
	RCK = 0;
}

/**
	* @brief 	LED点阵屏显示一列数据
	* @param	Column要选择的列，范围：0~7，0在最左边
	* @param	Data选择列显示的数据，高位在上，1为亮，0为灭
	* @retval	无
*/
void MatrixLED_ShowColumn(unsigned char Column, Data)
{
	_74HC595_WriteByte(Data);				//位选，数据通过74HC595寄存器，哪一位为1，则那一行的LED亮
	MATRIX_LED_PORT = ~(0x80 >> Column);	//段选，P0哪一位为0，则LED那一列就亮
	
	Delay(1);								// 消影
	MATRIX_LED_PORT = 0xFF; 				// P0口数据清0,段选位选完后，将段选清0
}