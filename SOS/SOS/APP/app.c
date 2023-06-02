/*
 * app.c
 *
 * Created: 5/30/2023 7:43:50 AM
 *  Author: Mcs
 */ 
#include "app.h"
#include "../SERVICE/sos/sos_config.h"
#include "../HAL/led/led_config.h"
#include "../STD_LIBRARIES/ex_int_manger/ex_int_manger_config.h"



static Std_ReturnType enu_sg_ret;
volatile static uint16_t u8_sg_counter;


static void Start_sos_handler(void)
{
	Start_Flag=1;
}

static void Stop_sos_handler(void)
{
	Start_Flag=2;
}


static void task_1_handler(void)
{
	LED_turn_toggle(&st_g_led0_instance);	
}



static void task_2_handler(void)
{	
	LED_turn_toggle(&st_g_led1_instance);
	u8_sg_counter++;
}

void APP_init()
{
	GLOBAL_InterruptEnable();
	
	enu_sg_ret |=SOS_init();
	if(SOS_E_NOK==enu_sg_ret)
	{
		// handle TASK fail initialization
	}
	enu_sg_ret = LED_initialize(&st_g_led0_instance);
	if(E_NOT_OK==enu_sg_ret)
	{
		// handle led fail initialization
	}
	enu_sg_ret |= LED_initialize(&st_g_led1_instance);
	if(E_NOT_OK==enu_sg_ret)
	{
		// handle led fail initialization
	}
	str_g_task_1_.Fptr_task_callBack = task_1_handler;
	enu_sg_ret |=SOS_create_task(&str_g_task_1_);
	if(SOS_E_NOK==enu_sg_ret)
	{
		// handle TASK fail initialization
	}
	str_g_task_2_.Fptr_task_callBack = task_2_handler;
	enu_sg_ret |=SOS_create_task(&str_g_task_2_);
	if(SOS_E_NOK==enu_sg_ret)
	{
		// handle TASK fail initialization
	}
/********************************************External interrupt for start & stop SOS********************************************************************/
       enu_sg_ret|= EXT_INTx_setCallBack_manger(&Start_sos_handler,INTERRUPT_EXTERNAL_INT0);
	   if (enu_sg_ret==E_NOT_OK)
	   {
		   // handle External interrupt fail set callback function 
	   }
	   else
	   {
		   //do nothing
	   }
       enu_sg_ret|= EXT_INTx_Init_manger(&s_INT0);
	    if (enu_sg_ret==E_NOT_OK)
	    {
		    // handle External interrupt fail initialization
	    }
		else
		{
			//do nothing
		}
		enu_sg_ret|= EXT_INTx_setCallBack_manger(&Stop_sos_handler,INTERRUPT_EXTERNAL_INT1);
		if (enu_sg_ret==E_NOT_OK)
		{
			// handle External interrupt fail set callback function
		}
		else
		{
			//do nothing
		}
		enu_sg_ret|= EXT_INTx_Init_manger(&s_INT1);
		if (enu_sg_ret==E_NOT_OK)
		{
			// handle External interrupt fail initialization
		}
		else
		{
			//do nothing
		}

}

void APP_start()
{	
		SOS_run();
}


