/*
 * uart.h
 *
 *  Created on: 30 Oca 2022
 *      Author: faruk.isiker
 */

#ifndef UART_H_
#define UART_H_
#include "inits.h"
#include "SETBIT.h"
#include "global_variables.h"
void uart_send_bytes(uart_config *uart,uint8_t *data,uint16_t length);
#endif /* UART_H_ */
