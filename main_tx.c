/* main_nodeA_TX.c */
#include "can2_driver.c"
#include "lcd.h"
void INIT_DISPLAY(void)
{
	LCD_COMMAND(0XC0);
	LCD_STR("V23CE6S2");
	LCD_COMMAND(0X80);
	LCD_STR("BODY CONTROL MODULE");
	delay_ms(500);
}

main(){	
	
	CAN2_MSG m1,m2,m3;
	can2_init();
	/*sending data frame*/
	m1.id=0x1;
	m1.rtr=0;//data frame
	m1.dlc=4;
	m1.byteA=0xDDCCBBAA;
	m1.byteB=0;
	
	m2.id=0x2;
	m2.rtr=0;//data frame
	m2.dlc=4;
	m2.byteA=0xDDCCBBAA;
	m2.byteB=0;
	
	m3.id=0x3;
	m3.rtr=0;//data frame
	m3.dlc=4;
	m3.byteA=0xDDCCBBAA;
	m3.byteB=0;

 	LCD_INIT();
	INIT_DISPLAY();
	IODIR0 = LED;
	IOSET0 = LED;
	
	while(1)
	{

		if(((IOPIN0>>sw2)&1)==0)
		{
			can2_tx(m2);//data-frame
			LCD_COMMAND(0X01);	
			LCD_COMMAND(0X80);
			LCD_STR("LEFT INDICATOR IS ON");
			delay_ms(1000);
			LCD_COMMAND(0X80);
			LCD_STR("LEFT INDICATOR IS OFF");
		}
		else if(((IOPIN0>>sw3)&1)==0)
		{
			can2_tx(m3);
			LCD_COMMAND(0X01);	
			LCD_COMMAND(0X80);
			LCD_STR("RIGHT INDICATOR IS ON");
			delay_ms(1000);
			LCD_COMMAND(0X80);
			LCD_STR("RIGHT INDICATOR IS OFF");
		}
		else if(((IOPIN0>>sw1)&1)==0)
		{	
			can2_tx(m1);
			LCD_COMMAND(0X01);			
			LCD_COMMAND(0X80);
			LCD_STR("WIPER IS ON");
			delay_ms(1000);
			LCD_COMMAND(0X80);
			LCD_STR("WIPER IS OFF");
		}
		else
		{
			LCD_COMMAND(0X01);	
			LCD_COMMAND(0X80);
			LCD_STR("PRESS SWITCH");
		}
	}
	
}

