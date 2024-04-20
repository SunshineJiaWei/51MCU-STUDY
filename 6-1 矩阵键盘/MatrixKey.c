#include <REGX52.H>
#include "Delay.h"

/**
	* @brief 读取矩阵键盘按下键码值
	* @param 无
	* @retval 按下键码值
	* 如果按下按键不松手，则程序会一直停留这此函数，松手后，返回按键键码值
*/

unsigned char MatrixKey()
{
	unsigned char MatrixNum = 0;
	
	// 选中第一列
	P1 = 0xFF;
	P1_3 = 0;
	if(P1_7 == 0) {Delay(20); while(P1_7 == 0); Delay(20); MatrixNum = 1;}
	if(P1_6 == 0) {Delay(20); while(P1_6 == 0); Delay(20); MatrixNum = 5;}
	if(P1_5 == 0) {Delay(20); while(P1_5 == 0); Delay(20); MatrixNum = 9;}
	if(P1_4 == 0) {Delay(20); while(P1_4 == 0); Delay(20); MatrixNum = 13;}
	
	// 选中第二列
	P1 = 0xFF;
	P1_2 = 0;
	if(P1_7 == 0) {Delay(20); while(P1_7 == 0); Delay(20); MatrixNum = 2;}
	if(P1_6 == 0) {Delay(20); while(P1_6 == 0); Delay(20); MatrixNum = 6;}
	if(P1_5 == 0) {Delay(20); while(P1_5 == 0); Delay(20); MatrixNum = 10;}
	if(P1_4 == 0) {Delay(20); while(P1_4 == 0); Delay(20); MatrixNum = 14;}
	
	// 选中第三列
	P1 = 0xFF;
	P1_1 = 0;
	if(P1_7 == 0) {Delay(20); while(P1_7 == 0); Delay(20); MatrixNum = 3;}
	if(P1_6 == 0) {Delay(20); while(P1_6 == 0); Delay(20); MatrixNum = 7;}
	if(P1_5 == 0) {Delay(20); while(P1_5 == 0); Delay(20); MatrixNum = 11;}
	if(P1_4 == 0) {Delay(20); while(P1_4 == 0); Delay(20); MatrixNum = 15;}
	
	// 选中第四列
	P1 = 0xFF;
	P1_0 = 0;
	if(P1_7 == 0) {Delay(20); while(P1_7 == 0); Delay(20); MatrixNum = 4;}
	if(P1_6 == 0) {Delay(20); while(P1_6 == 0); Delay(20); MatrixNum = 8;}
	if(P1_5 == 0) {Delay(20); while(P1_5 == 0); Delay(20); MatrixNum = 12;}
	if(P1_4 == 0) {Delay(20); while(P1_4 == 0); Delay(20); MatrixNum = 16;}
	
	return MatrixNum;
}