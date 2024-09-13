#include<LPC21XX.H>
//#include"delay.h"
#define LCD_D 0xf<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19
void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INTEGER(int );
void LCD_STR(char*);
void LCD_FLOAT(float );
void LCD_INIT(void)
{
	IODIR1= LCD_D|RS|RW|E;
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X02);
	LCD_COMMAND(0X0C);
	LCD_COMMAND(0X28);
	LCD_COMMAND(0X80);
}
void LCD_COMMAND(unsigned char cmd)
{
	IOPIN1 = (cmd&(0xf0))<<16;
	IOCLR1 = RS;
	IOCLR1 = RW;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
	
	IOPIN1 = (cmd&(0x0f))<<20;
	IOCLR1 = RS;
	IOCLR1 = RW;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
}
void LCD_DATA(unsigned char d)
{
	IOPIN1 = (d&(0xf0))<<16;
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
	
	IOPIN1 = (d&(0x0f))<<20;
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
}
void LCD_INTEGER(int x)
{
	signed char i =0;
	unsigned char arr[5];
	if(x == 0)
		LCD_DATA('0');
	else 
	{
		if (x < 0)
		{
			LCD_DATA('-');
			x = -x;
		}

// 		if(x < 10)
// 		{
// 			LCD_DATA(x+48);
// 		}
// 		 
// 		else if(x < 100)
// 		{
// 			LCD_DATA((x/10)+48);
// 			LCD_DATA((x%10)+48);
// 		}

		else
		{
			while(x != 0)
			{
					arr[i++] = x%10;
					x = x/10;	
			}
			for(--i;i>=0;i--)
					LCD_DATA(arr[i]+48);
		}	
	}
}
void LCD_STR(char*s)
{
	while(*s)
		LCD_DATA(*s++);
}
void LCD_FLOAT(float f)
{
	int temp;
	temp = f;
	LCD_INTEGER(temp);
	LCD_DATA('.');
	temp = ((f - temp)*10000);
	LCD_INTEGER(temp);
}

void LCD_ROTATE(char *s)
{
	int i,x,n,j;
	for(x=0;*s;x++,s++);
		s--;
	while(j != 50)
	{
			j++;
			LCD_COMMAND(0X01);
			LCD_COMMAND(0X80|i++);
			LCD_STR(s);
			delay_ms(100);
			n = i+x;
			if(n > 16)
			{
				n = n - 16;
				while(n--)
				{
					LCD_COMMAND(0X80|n);
					LCD_DATA(*s--);
				}
			}
			if(i==16)
				i=0;
			delay_ms(500);
	}
}
