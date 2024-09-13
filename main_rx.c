/* main_nodeA_TX.c */
#include "can2_driver.c"
main(){	
	CAN2_MSG m1;
	can2_init();
	uart0_init(115200);
	uart0_tx_string("nodeB TESTING CAN\r\n");
	IODIR0 |= motor1|motor2;
	IOSET0|=motor1|motor2;
while(1)
	{			 
	  can2_rx(&m1);
		if(m1.id==0x1)
		{
// 				IOCLR0=LED;			
				IOCLR0=motor1;
				IOSET0=motor2;
				delay_ms(1000);
// 			IOSET0=LED;
				IOCLR0=motor2;
 				IOSET0=motor1;
				delay_ms(1000);

		}	
//		else
//		{
  				IOSET0|=motor1|motor2;
// 				IOSET0=motor2;
// 				IOSET0 = LED;
//		}	
		}
	
}
