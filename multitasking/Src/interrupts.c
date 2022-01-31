#include "interrupts.h"

void TIM7_IRQHandler(void)
{
    g_timer_overflow++;
    TIM7->SR=0;                         // clear Timer Int flag
}
void USART1_IRQHandler(void){

}
void USART2_IRQHandler(void){

}
void USART3_IRQHandler(void){
	if(g_index == SIZEOFRX) g_index = 0;
	if(g_index == 0)	g_check_rx = 1;
	g_uart_rx_interrupt[g_index++] = USART3->DR;
}
