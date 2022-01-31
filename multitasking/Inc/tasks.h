/*
 * tasks.h
 *
 *  Created on: 31 Oca 2022
 *      Author: faruk.isiker
 */

#ifndef TASKS_H_
#define TASKS_H_
#include "global_variables.h"
#include "SETBIT.h"
#include "string.h"
#include "stdio.h"
#include "uart.h"

void parsing_task();
void led_drive(uint16_t on_ms,uint16_t off_ms);

#endif /* TASKS_H_ */
