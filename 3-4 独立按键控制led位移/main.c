#include <REGX52.H>

void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
	
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
	
}

void main()
{
	
	unsigned char ledRegister = 1;
	P2 = 0xFE;
	
	while(1)
	{
		
		// k1 
		if(P3_1 == 0)
		{
			Delay(20);
			while(P3_1 == 0);
			Delay(20);
			
			if(ledRegister == 1) 
				ledRegister = 0x80;
			else 
				ledRegister = ledRegister >> 1;
			P2 = ~ledRegister;
			
		}
		
		// k2
		if(P3_0 == 0)
		{
			Delay(20);
			while(P3_0 == 0);
			Delay(20);
			
			if(ledRegister == 0x80)
				ledRegister = 1;
			else
				ledRegister = ledRegister << 1;
			P2 = ~ledRegister;
			
		}
		
	}

}