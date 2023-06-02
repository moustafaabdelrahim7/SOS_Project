/*
 * ex_int_manger_config.c
 *
 * Created: 6/1/2023 9:59:52 AM
 *  Author: AIO
 */ 

#include "ex_int_manger.h"
//#include "ex_int_manger_config.h"

Interrupt_Config_t s_INT0 = {
	.source_id = INTERRUPT_EXTERNAL_INT0,
	.edge = INTERRUPT_RISING_EDGE
};
Interrupt_Config_t s_INT1 = {
	.source_id = INTERRUPT_EXTERNAL_INT1,
	.edge = INTERRUPT_RISING_EDGE
};