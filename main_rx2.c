/* main_nodeA_TX.c */
#include "can2_driver.c"
#define LED 1<<17
main(){	
	CAN2_MSG m1;
    IODIR0=LED;
	can2_init();
	uart0_init(115200);
	uart0_tx_string("nodeB TESTING CAN\r\n");
	IODIR0 |= motor1|motor2;
	IOSET0|=motor1|motor2;
while(1)
	{			 
	  can2_rx(&m1);
		if(m1.id==0x3)
		{
            IOCLR0=LED;
            delay_ms(200);
            IOSET0=LED;
		}	
		else
		{
 				IOSET0 = LED;
		}	
		}
	
}