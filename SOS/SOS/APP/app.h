/*
 * app.h
 *
 * Created: 5/30/2023 7:44:02 AM
 *  Author: Mcs
 */ 


#ifndef APP_H_
#define APP_H_

#include "../SERVICE/sos/sos.h"
#include "../HAL/led/led.h"
#include "../STD_LIBRARIES/ex_int_manger/ex_int_manger.h"



extern volatile uint8_t Start_Flag;


void APP_init(void);

void APP_start(void);

#endif /* APP_H_ */