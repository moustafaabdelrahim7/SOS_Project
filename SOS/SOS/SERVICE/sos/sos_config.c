/*
 * sos_config.c
 *
 * Created: 5/30/2023 4:19:21 AM
 *  Author: Mcs
 */ 
 #include "sos_config.h"
 #include "sos.h" 
 

 
 str_task_control_data_t  str_g_task_1_ = {
	.enu_task_state = TASK_IDLE_STATE,
	.u16_task_priodic_time = 300,
	.u8_task_id = 1,
	.u8_task_priority = 2,
 };
 
  str_task_control_data_t  str_g_task_2_ = {
	  .enu_task_state = TASK_IDLE_STATE,
	  .u16_task_priodic_time = 500,
	  .u8_task_id = 2,
	  .u8_task_priority = 1,
 };
 
  str_task_control_data_t  str_g_task_3_ = {
	  .enu_task_state = TASK_IDLE_STATE,
	  .u16_task_priodic_time = 1000,
	  .u8_task_id = 3,
	  .u8_task_priority = 8,
  };
