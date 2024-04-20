#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"

unsigned char KeyNum;
unsigned int C_Password, Count, B_Password = 2345;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	
	while(1)
	{
		KeyNum = MatrixKey(); 
		if(KeyNum)
		{
			// 密码区
			if(KeyNum <= 10 && Count < 4)
			{
				C_Password *= 10;
				C_Password += KeyNum;
				Count++;
				LCD_ShowNum(2,1,C_Password,4);
			}
			
			// 1、确认 2、输入四位密码后自动判断正误
			if(KeyNum == 11 || Count == 4)
			{
				if(C_Password == B_Password)
				{
					LCD_ShowString(1,14,"OK ");
					
				}
				else
				{
					LCD_ShowString(1,14,"ERR");
				}
				C_Password = 0; // 密码清空
				Count = 0;		// 次数清空
				LCD_ShowNum(2,1,C_Password,4); // 更新显示
			}
			
			// 取消
			if(KeyNum == 12)
			{
				C_Password = 0;
				Count = 0;
				LCD_ShowNum(2,1,C_Password,4);
			}
			
			// 删除
			if(KeyNum == 13)
			{
				C_Password /= 10;
				Count--;
				LCD_ShowNum(2,1,C_Password,4);
			}
			
			// 修改密码
			if(KeyNum == 14)
			{
				C_Password = 0; // 密码清空
				Count = 0;		// 次数清空
				LCD_ShowNum(2,1,C_Password,4);
				LCD_ShowString(1,14,"UPD"); // 显示状态
				// 因为密码是4位，所以执行4次循环
				while(Count < 4)
				{
					KeyNum = MatrixKey(); 
					// 输入密码
					if(KeyNum != 0 && KeyNum <= 10 && Count < 4)
					{
						C_Password *= 10;
						C_Password += KeyNum;
						Count++;
						LCD_ShowNum(2,1,C_Password,4);
						
					}
				}
				// 4位密码输入完毕，执行修改密码
				B_Password = C_Password;
				LCD_ShowString(1,14,"ok "); // 显示状态
				C_Password = 0; // 密码清空
				Count = 0;		// 次数清空
				LCD_ShowNum(2,1,C_Password,4);
			}
		
		}
		
	}
}