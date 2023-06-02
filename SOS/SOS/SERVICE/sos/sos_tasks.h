/*
 * sos_config.h
 *
 * Created: 5/30/2023 4:19:12 AM
 *  Author: Mcs
 */ 


#ifndef SOS_TASKS_H_
#define SOS_TASKS_H_

#include "sos.h"


 #define PERIODIC_TASK_EVERY_3_SEC		300U
 #define TASK_ONE_ID					1U
 #define TASK_PRIORITY_EQUAL_ONE		1U


extern  str_task_control_data_t  str_g_task_1_;
extern  str_task_control_data_t  str_g_task_2_;
extern  str_task_control_data_t  str_g_task_3_;


#endif /* SOS_TASKS_H_ */