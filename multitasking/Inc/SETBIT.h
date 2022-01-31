/*
 * SETBIT.h
 *
 *  Created on: 29 Oca 2022
 *      Author: faruk.isiker
 */

#ifndef SETBIT_H_
#define SETBIT_H_
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#define IS_SET(number,position) (number && (1U << position))

#define SET_GPIOD(x)		GPIOD->BSRR |= (1U<<x)
#define RESET_GPIOD(x)		GPIOD->BSRR |= (1U<<(x+16))
#define TOGGLE_GPIOD(x)		GPIOD->BSRR |= (GPIOD->ODR && (1U<<x)) ? (1U<<(x+16)) : (1U<<x);
#endif /* SETBIT_H_ */
