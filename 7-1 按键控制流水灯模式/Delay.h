/*
	1、当文件编译到这一行，如果这个文件还没有被编译过，也就是首次编译，就会执行后续的`define xxx这句话，把后续的代码定义一次。 反之，则不会再重复编译
	2、可能会出现重复定义的错误
*/
#ifndef __DELAY_H__

#define __DELAY_H__

void Delay(unsigned char xms);

#endif