/*
 * timer_manger_config.c
 *
 * Created: 5/30/2023 4:29:19 AM
 *  Author: Mcs
 */ 
 #include "timer_manager.h"
 #include "timer_manger_config.h" 
 
 st_timerConfigType st_g_sos_timer = {
	.u8_timerNum = TIMER_0,
	.u8_timerClock = TIMER_F_CPU_1024,
	.u16_timer_InitialValue =248,
	.u8_timer_ovf_int_enable = TIMER_INTERRUPT_FEATURE_ENABLE,
 };
 