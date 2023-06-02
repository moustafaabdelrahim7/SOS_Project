/*
 * ex_int_manger.h
 *
 * Created: 6/1/2023 9:59:12 AM
 *  Author: AIO
 */ 


#ifndef EX_INT_MANGER_H_
#define EX_INT_MANGER_H_

#include "../../MCAL/exti/external_interrupt.h"

Std_ReturnType EXT_INTx_setCallBack_manger(void(*a_fptr)(void),  Interrupt_ID_t a_interrupt_number );

Std_ReturnType EXT_INTx_Init_manger( Interrupt_Config_t *Interrupt_Config_Ptr );

Std_ReturnType EXT_INTx_setEdgeType_manger(Interrupt_Edge_type_t a_edgeType ,  Interrupt_ID_t a_interrupt_Id);

Std_ReturnType EXT_INTx_DeInit_manger(const Interrupt_ID_t a_interrupt_Id);











#endif /* EX_INT_MANGER_H_ */