/*
 * led_config.h
 *
 * Created: 5/27/2023 7:02:09 AM
 *  Author: Mcs
 */ 


#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

#include "led.h"

 #define PERIODIC_TASK_EVERY_3_SEC		300U
 #define TASK_ONE_ID					1U
 #define TASK_PRIORITY_EQUAL_ONE		1U

extern led_t st_g_led0_instance ;
extern led_t st_g_led1_instance ;
extern led_t st_g_led2_instance ;



#endif /* LED_CONFIG_H_ */