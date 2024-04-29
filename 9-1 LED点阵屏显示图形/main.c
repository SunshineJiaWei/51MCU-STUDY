#include <REGX52.H>
#include "Delay.h"
#include "MatrixLED.h"

sbit RCK = P3^5;	// RCLK
sbit SCK = P3^6;	// SRCLK
sbit SER = P3^4;	// SER

#define MATRIX_LED_PORT		P0



void main()
{
	SER = 0;
	RCK = 0;
	
	while(1)
	{
		MatrixLED_ShowColumn(0, 0x3C);
		MatrixLED_ShowColumn(1, 0x42);
		MatrixLED_ShowColumn(2, 0xA9);
		MatrixLED_ShowColumn(3, 0x85);
		MatrixLED_ShowColumn(4, 0x85);
		MatrixLED_ShowColumn(5, 0xA9);
		MatrixLED_ShowColumn(6, 0x42);
		MatrixLED_ShowColumn(7, 0x3C);
	}
}   