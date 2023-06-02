/*
 * SOS.c
 *
 * Created: 5/30/2023 2:21:23 AM
 * Author : Mcs
 */ 

//#include <avr/io.h>
#include "APP/app.h"




//#include <util/delay.h>
#define  F_CPU 8000000UL



int main(void)
{
	APP_init();
	APP_start();

}





/*
    / Replace with your application code 
	APP_init();
// 	GLOBAL_InterruptEnable();
// 	LED_initialize(&st_g_led0_instance);
// 	st_g_sos_timer.callBackFunction = SOS_timer_handelr2;
// 	TIMER_Manager_init(&st_g_sos_timer);
// 	TIMER_Manager_start(&st_g_sos_timer);
	APP_start();
	

	

/*_delay_ms(1000);
    while (1) 
    {
		
// 		 LED_turn_off(&st_g_led0_instance);
// 		 LED_turn_off(&st_g_led1_instance);
/*

		LED_turn_toggle(&st_g_led0_instance);
    }
	*/

