/*
 * global_variables.h
 *
 *  Created on: Jan 29, 2022
 *      Author: faruk.isiker
 */

#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_
#include "inits.h"
extern unsigned long g_timer_overflow;
#define SIZEOFRX 15
extern char g_uart_rx_interrupt[SIZEOFRX];
extern char g_uart_rx_interrupt_copied[SIZEOFRX];
extern unsigned int g_led_on;
extern unsigned int g_led_off;
extern unsigned int g_check_rx;
extern unsigned int  g_index;
extern uart_config uart3;
extern int echo;



#endif /* GLOBAL_VARIABLES_H_ */
