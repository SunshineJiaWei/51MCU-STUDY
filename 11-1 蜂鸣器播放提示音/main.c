#include <REGX52.H>
#include "Key.h"
#include "NixieTube.h"
#include "Buzzer.h"

unsigned char KeyNum;

void main() 
{
	NixieTube(1,0);
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			Buzzer_Time(100);
			NixieTube(1,KeyNum);
		}
	}
}