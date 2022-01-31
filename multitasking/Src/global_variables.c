/*
 * global_variables.c
 *
 *  Created on: Jan 29, 2022
 *      Author: faruk.isiker
 */
#include "global_variables.h"
unsigned long g_timer_overflow = 0;
char g_uart_rx_interrupt[SIZEOFRX] = "";
char g_uart_rx_interrupt_copied[SIZEOFRX] = "";
unsigned int g_led_on = 500;
unsigned int g_led_off = 500;
unsigned int g_check_rx = 0;
unsigned int  g_index = 0;
uart_config uart3;
int echo = 0;
