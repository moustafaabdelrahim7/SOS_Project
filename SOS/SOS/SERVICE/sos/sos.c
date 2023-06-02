/*
 * sos.c
 *
 * Created: 5/30/2023 2:27:45 AM
 *  Author: Mcs
 */ 
#include "sos.h"
#include "../../STD_LIBRARIES/timer_manager/timer_manager.h"
#include "../../STD_LIBRARIES/timer_manager/timer_manger_config.h"
#include "../../HAL/led/led_config.h"

#include "../../MCAL/timer/timer_private_reg.h"

static enu_sos_init_status_t enu_sg_sos_init_status = SOS_FLAG_NOT_INITIALIZED;

static str_task_control_data_t *strPtrs_tasks[SOS_TASKS_MAX_NUM];

static volatile uint32_t u8_sg_sos_time_counter;
static volatile uint32_t u8_sg_sos_time_counter_2_;

static uint8_t flag =0;
static uint8_t flag_2_ =0;

 volatile uint8_t u8_sg_sos_enable_flag = TRUE;
 

static uint8_t u8_sg_sos_task_counter;

static uint8_t u8_sg_sos_running_state_status = SOS_RUNNING_STATE_IS_FREE;

volatile static uint32_t u8Arr_sg__of_taskCounters[SOS_TASKS_MAX_NUM]={0};

volatile static  uint32_t uintu8_sg_sos_index_1;
volatile static  uint32_t uintu8_sg_sos_index_2;

volatile uint8_t Start_Flag=2;


/*static enu_sos_status_t sort_tasks_priority(void);*/

volatile static uint8_t u8Arr_sg_ID_of_taskPriorty[SOS_TASKS_MAX_NUM]; 

static enu_sos_status_t init_theArrayOfIDs(void);
 


static void SOS_timer_handelr(void)
{


	for(uintu8_sg_sos_index_1=0;uintu8_sg_sos_index_1<SOS_TASKS_MAX_NUM;uintu8_sg_sos_index_1++)
	{
		u8Arr_sg__of_taskCounters[uintu8_sg_sos_index_1]++;
	}	


	TIMER_Manager_reset(&st_g_sos_timer);
}




/********************************/

enu_sos_status_t SOS_init (void)
{
	enu_sos_status_t enu_l_sos_ret = SOS_E_OK;
	uint8_t u8_l_task_index = ZERO_INIT;
	if((SOS_FLAG_NOT_INITIALIZED==enu_sg_sos_init_status))
	{
		 // initialize the timer
		 st_g_sos_timer.callBackFunction = SOS_timer_handelr;
		 enu_l_sos_ret = TIMER_Manager_init(&st_g_sos_timer);
		 if(TIMER_E_NOT_OK==enu_l_sos_ret)
		 {
			 enu_l_sos_ret = SOS_TIMER_E_NOK;
		 }
		 else
		 {
			// initialize all task status with idle state
			if (strPtrs_tasks!=NULL)
			{
				for(u8_l_task_index = ZERO_INIT;u8_l_task_index<SOS_TASKS_MAX_NUM;u8_l_task_index++)
				{
					strPtrs_tasks[u8_l_task_index] = NULL;
				}
			}
			else
			{
				enu_l_sos_ret = SOS_DATA_BASE_NOT_EXIST;
			}
			
			enu_sg_sos_init_status = SOS_FLAG_INITIALIZED;
			
		 }	/*end of if*/ 
		 
	}
	
	else
	{
		enu_l_sos_ret = SOS_ALREADY_INITIALIZED;
	}
	return enu_l_sos_ret;
}


enu_sos_status_t SOS_deinit (void)
{
	enu_sos_status_t enu_l_sos_ret = SOS_E_OK;
	uint8_t u8_l_task_index = ZERO_INIT;
	if((SOS_FLAG_INITIALIZED==enu_sg_sos_init_status))
	{
		// de-initialize the timer
		st_g_sos_timer.callBackFunction = NULL;
		//enu_l_sos_ret = TIMER_Manager_deinit(&st_g_sos_timer);
		enu_l_sos_ret = TIMER_Manager_stop(st_g_sos_timer.u8_timerNum);
		if(TIMER_E_NOT_OK==enu_l_sos_ret)
		{
			enu_l_sos_ret = SOS_TIMER_E_NOK;
		}
		else
		{
			// Validate the tasks data base  
			if (strPtrs_tasks!=NULL)
			{
				// de-initialize all task data base with null
				for(u8_l_task_index = ZERO_INIT;u8_l_task_index<SOS_TASKS_MAX_NUM;u8_l_task_index++)
				{
					strPtrs_tasks[u8_l_task_index] = NULL;
				}
			}
			else
			{
				enu_l_sos_ret = SOS_DATA_BASE_NOT_EXIST;
			}
			
			enu_sg_sos_init_status = SOS_FLAG_NOT_INITIALIZED;
		}
	}
	else
	{
		enu_l_sos_ret = SOS_NOT_INITIALIZED;
	}
	return enu_l_sos_ret;
}

/******************************************************************************/

/*to return void */

enu_sos_status_t SOS_run (void)
{		
	while (TRUE)
	{
		if (Start_Flag==1)
		{
			enu_sos_status_t  enu_l_sos_ret = SOS_E_OK;
			uint8_t u8_l_task_index = ZERO_INIT;
			uint8_t u8_l_timerStopFlag = ZERO_INIT;
	
			if((SOS_FLAG_INITIALIZED==enu_sg_sos_init_status))
			{
				enu_l_sos_ret = TIMER_Manager_start(&st_g_sos_timer);
		
				if(TIMER_E_NOT_OK==enu_l_sos_ret)
				{
					enu_l_sos_ret = SOS_TIMER_E_NOK;
				}
				else
				{
						enu_l_sos_ret = init_theArrayOfIDs();

							for(uintu8_sg_sos_index_2=0;uintu8_sg_sos_index_2<SOS_TASKS_MAX_NUM;uintu8_sg_sos_index_2++)
							{
								if((strPtrs_tasks[u8Arr_sg_ID_of_taskPriorty[uintu8_sg_sos_index_2]]->u16_task_priodic_time)==
								(u8Arr_sg__of_taskCounters[u8Arr_sg_ID_of_taskPriorty[uintu8_sg_sos_index_2]]))
								{
									(strPtrs_tasks[u8Arr_sg_ID_of_taskPriorty[uintu8_sg_sos_index_2]]->Fptr_task_callBack)();		
									u8Arr_sg__of_taskCounters[u8Arr_sg_ID_of_taskPriorty[uintu8_sg_sos_index_2]]=0;
								}
							}
					}
		
			}
			else
			{
				enu_l_sos_ret = SOS_E_NOK;
			}
			}
	
		else if (Start_Flag==2)
		{
			SOS_disable();
		}
	
	}
}


/*************************************/
enu_sos_status_t SOS_disable (void)
{
	enu_sos_status_t enu_l_sos_ret = SOS_E_OK;
	if((SOS_FLAG_INITIALIZED==enu_sg_sos_init_status))
	{
		//stop the timer
		enu_l_sos_ret = TIMER_Manager_stop(st_g_sos_timer.u8_timerNum);
		if(TIMER_E_NOT_OK==enu_l_sos_ret)
		{
			enu_l_sos_ret = TIMER_E_NOT_OK;
		}
		else
		{
			u8_sg_sos_enable_flag = FALSE;
		}
		
	}
	else
	{
		enu_l_sos_ret = SOS_NOT_INITIALIZED;
	}
	return enu_l_sos_ret;
}

/**************************************/

/*we need to make sure that we don't access a null ptr*/
enu_sos_status_t SOS_create_task (str_task_control_data_t *strPtr_task_control_data)
{
	enu_sos_status_t enu_l_sos_ret = SOS_E_OK;
	uint8_t u8_l_task_index_3_ = ZERO_INIT;
	if (strPtr_task_control_data->u8_task_id < SOS_TASKS_MAX_NUM)
	{
		if ((strPtr_task_control_data->Fptr_task_callBack!=NULL) && (strPtr_task_control_data)  &&
		 enu_sg_sos_init_status==SOS_FLAG_INITIALIZED && strPtrs_tasks[strPtr_task_control_data->u8_task_id]->Fptr_task_callBack==NULL)
		{
			strPtrs_tasks[strPtr_task_control_data->u8_task_id]                        =strPtr_task_control_data;
		}
		else
		{
			/*task id already exist*/
			enu_l_sos_ret=SOS_E_NOK;
		}
	}
	else
	{
		enu_l_sos_ret=SOS_E_NOK;
	}

	return enu_l_sos_ret;

}


/*****************************************/



enu_sos_status_t SOS_modify_task (uint8_t u8_a_oldTask_id , str_task_control_data_t *strPtr_new_task_control_data )
{
	enu_sos_status_t enu_l_sos_ret = SOS_E_OK;
	uint8_t u8_l_task_index = ZERO_INIT;
	if((SOS_FLAG_INITIALIZED==enu_sg_sos_init_status) && (strPtr_new_task_control_data))
	{
	
		 for(u8_l_task_index = ZERO_INIT;u8_l_task_index<SOS_TASKS_MAX_NUM;u8_l_task_index++)
		 {
			 if((u8_a_oldTask_id==strPtrs_tasks[u8_l_task_index]->u8_task_id) && (strPtrs_tasks[u8_l_task_index] != NULL))
			 {
				  // modify the task by storing its' new control data into the task data-base and update it's state to be ready to run
				  strPtrs_tasks[u8_l_task_index]->u8_task_id		    = strPtr_new_task_control_data->u8_task_id;
				  strPtrs_tasks[u8_l_task_index]->enu_task_state		= TASK_READY_STATE;
				  strPtrs_tasks[u8_l_task_index]->u8_task_priority	    = strPtr_new_task_control_data->u8_task_priority;
				  strPtrs_tasks[u8_l_task_index]->u16_task_priodic_time = strPtr_new_task_control_data->u16_task_priodic_time;
				  strPtrs_tasks[u8_l_task_index]->Fptr_task_callBack    = strPtr_new_task_control_data->Fptr_task_callBack;
				   break;
			 }
			 else
			 {
				 //do nothing
			 }
			
		 }
		/*we need to make sure that we have the id that being  modified*/ 
		
	}
	else
	{
		enu_l_sos_ret = SOS_E_NOK;
	}
	return enu_l_sos_ret;
}

/**************************************************/
/*same comment as the previous one */
enu_sos_status_t SOS_delete_task (uint8_t u8_a_Task_id)
{
	enu_sos_status_t enu_l_sos_ret = SOS_E_OK;
	uint8_t u8_l_task_index = ZERO_INIT;
	if( (SOS_FLAG_INITIALIZED==enu_sg_sos_init_status) && (u8_a_Task_id<SOS_TASKS_MAX_NUM) )
	{
		for(u8_l_task_index = ZERO_INIT;u8_l_task_index<SOS_TASKS_MAX_NUM;u8_l_task_index++)
		{
			if(u8_a_Task_id== strPtrs_tasks[u8_l_task_index]->u8_task_id)
			{
				strPtrs_tasks[u8_l_task_index]->u8_task_id			  = ZERO;
				strPtrs_tasks[u8_l_task_index]->enu_task_state		  = TASK_TERMINATED_STATE;
				strPtrs_tasks[u8_l_task_index]->u8_task_priority	  = ZERO;
				strPtrs_tasks[u8_l_task_index]->u16_task_priodic_time = ZERO;
				strPtrs_tasks[u8_l_task_index]->Fptr_task_callBack    = NULL;
				strPtrs_tasks[u8_l_task_index] = NULL;
			}
			else
			{
				enu_l_sos_ret = SOS_E_NOK;	// AS IF THE TASK DID NOT BE CREATED IN THE FIRST PLACE 
			}
			
		}
		
	}
	else
	{
		enu_l_sos_ret = SOS_E_NOK;
	}
	return enu_l_sos_ret;
}




static enu_sos_status_t init_theArrayOfIDs(void)
{
	enu_sos_status_t enu_l_sos_ret = SOS_E_OK;
	uint8_t u8_l_task_index_1_ = ZERO_INIT;//be more descriptive 
	uint8_t u8_l_task_index_2_ = ZERO_INIT;
	uint8_t u8_l_task_index_3_ = ZERO_INIT;
	uint8_t  u8_l_temp = ZERO_INIT;
	if((SOS_FLAG_INITIALIZED==enu_sg_sos_init_status))
	{
	
		for(u8_l_task_index_1_ = ZERO_INIT;u8_l_task_index_1_<SOS_TASKS_MAX_NUM;u8_l_task_index_1_++)
		{
			for(u8_l_task_index_2_ = u8_l_task_index_1_ + 1 ; u8_l_task_index_2_<SOS_TASKS_MAX_NUM ; u8_l_task_index_2_++)
			{
				
				if((strPtrs_tasks[u8_l_task_index_1_ ]->u8_task_priority) < (strPtrs_tasks[u8_l_task_index_2_]->u8_task_priority))
				{
				
					u8Arr_sg_ID_of_taskPriorty[u8_l_task_index_3_] =  strPtrs_tasks[u8_l_task_index_1_]->u8_task_id;
					u8_l_task_index_3_++;
				}
				else if((strPtrs_tasks[u8_l_task_index_1_ ]->u8_task_priority) > (strPtrs_tasks[u8_l_task_index_2_]->u8_task_priority))
				{
					
					u8Arr_sg_ID_of_taskPriorty[u8_l_task_index_3_] = strPtrs_tasks[u8_l_task_index_2_]->u8_task_id;
					u8_l_task_index_3_++;
				}
				
				else
				{
					
				}
			}
		}
	}
	else
	{
		enu_l_sos_ret = SOS_E_NOK;
	}
	return enu_l_sos_ret;
}
