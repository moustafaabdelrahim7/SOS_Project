/*
 * ex_int_manger.c
 *
 * Created: 6/1/2023 9:58:41 AM
 *  Author: AIO
 */ 


#include "ex_int_manger.h"


Std_ReturnType EXT_INTx_setCallBack_manger(void(*a_fptr)(void),  Interrupt_ID_t a_interrupt_number )
{
	Std_ReturnType ret = E_OK;
	if(NULL == a_fptr || a_interrupt_number > NUM_OF_EXT_INTx - 1)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret=EXT_INTx_setCallBack(a_fptr,a_interrupt_number);
	}
	return ret;
}

Std_ReturnType EXT_INTx_Init_manger( Interrupt_Config_t *Interrupt_Config_Ptr )
{
	Std_ReturnType ret = E_OK;
	if(NULL == Interrupt_Config_Ptr || Interrupt_Config_Ptr->source_id > NUM_OF_EXT_INTx - 1)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret=EXT_INTx_Init(Interrupt_Config_Ptr);
	}
	return ret;
}

Std_ReturnType EXT_INTx_setEdgeType_manger(Interrupt_Edge_type_t a_edgeType ,  Interrupt_ID_t a_interrupt_Id)
{
	Std_ReturnType ret = E_OK;
	if(a_interrupt_Id > NUM_OF_EXT_INTx - 1 || a_edgeType > NOT_VALID_EDGE)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret=EXT_INTx_setEdgeType(a_edgeType,a_interrupt_Id);
	}
	return ret;
}

Std_ReturnType EXT_INTx_DeInit_manger(const Interrupt_ID_t a_interrupt_Id)
{
	Std_ReturnType ret = E_OK;
	if(a_interrupt_Id > NUM_OF_EXT_INTx - 1)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret=EXT_INTx_DeInit(a_interrupt_Id);
	}
	return ret;
}