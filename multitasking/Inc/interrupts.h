/*
 * interrupts.h
 *
 *  Created on: Jan 29, 2022
 *      Author: faruk.isiker
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_
#include "stm32f407xx.h"
#include "string.h"
#include "stdlib.h"
#include "global_variables.h"
#include "uart.h"
void TIM7_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
#endif /* INTERRUPTS_H_ */
