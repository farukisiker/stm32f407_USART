/*
 * uart.c
 *
 *  Created on: 30 Oca 2022
 *      Author: faruk.isiker
 */
#include "uart.h"
/*
 * Procedure:
1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
2. Program the M bit in USART_CR1 to define the word length.
3. Program the number of stop bits in USART_CR2.
4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
place. Configure the DMA register as explained in multibuffer communication.
5. Select the desired baud rate using the USART_BRR register.
6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
for each data to be transmitted in case of single buffer.
8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
that the transmission of the last frame is complete. This is required for instance when
the USART is disabled or enters the Halt mode to avoid corrupting the last
transmission.
 */
#define UNUSED(x) (void)(x)

void uart_send_bytes(uart_config *uart,uint8_t *data,uint16_t length){
	uint32_t read_sr;
	UNUSED(read_sr);
	SET_BIT(uart->uart_com->CR1, USART_CR1_TE);
	while(length>0){
		read_sr = uart->uart_com->SR;
		uart->uart_com->DR = *data;
		while((uart->uart_com->SR & USART_SR_TXE) != USART_SR_TXE){
			__NOP();
		}
		length--;
		data++;
	}
	while((uart->uart_com->SR & USART_SR_TC) != USART_SR_TC);
	CLEAR_BIT(uart->uart_com->CR1, USART_CR1_TE);
}

