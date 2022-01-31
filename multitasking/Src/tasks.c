/*
 * tasks.c
 *
 *  Created on: 31 Oca 2022
 *      Author: faruk.isiker
 */
#include "tasks.h"

const char start[] = "start";
const char stop[] = "stop";
const char ledon[] = "ledon=";
const char ledoff[] = "ledoff=";

static uint16_t char2int(char *s){
	int temp = 0;
	while((*s) != '\0')
	{
		if(*s<=57 || *s>=48){
			temp = (temp*10) + (int)(*s-48);
		}else
			return 0;

		s++;
	}
	return temp;
}

void led_drive(uint16_t on_ms,uint16_t off_ms);


static void send_after_1ms(){
	static int flag = 1;
	static uint32_t temp = 0;
	if(flag == 1){
		g_timer_overflow = 0;
		temp = g_timer_overflow;
		flag = 0;
	}
	if(g_timer_overflow>(temp+2)){
		uart_send_bytes(&uart3, (uint8_t*)g_uart_rx_interrupt,strlen(g_uart_rx_interrupt));
		memset((char*)g_uart_rx_interrupt,'\0',sizeof(g_uart_rx_interrupt)/sizeof(g_uart_rx_interrupt[0]));
		g_index = 0;
		g_check_rx = 0;
		flag = 1;
	}
}

static void echo_task(){
	if(echo == 0){
		if(g_timer_overflow >= 1000){
				TOGGLE_GPIOD(13);
				g_timer_overflow = 0;
				g_check_rx = 0;
				memset((char*)g_uart_rx_interrupt,'\0',sizeof(g_uart_rx_interrupt)/sizeof(g_uart_rx_interrupt[0]));
				g_index = 0;
		}
	}else{
		if(g_check_rx == 1)
			send_after_1ms();
	}
}


void led_drive(uint16_t on_ms,uint16_t off_ms){
	if(echo == 1){
		static uint8_t on_off_flag = 0;
		switch (on_off_flag) {
			case 0://off
				if(g_timer_overflow > off_ms){
					g_timer_overflow = 0;
					SET_GPIOD(13);
					on_off_flag = 1;
				}
				break;
			case 1://on
				if(g_timer_overflow > on_ms){
					g_timer_overflow = 0;
					RESET_GPIOD(13);
					on_off_flag = 0;
				}
				break;
			default:
				break;
		}
	}

}
void parsing_task(){
	if(strncmp(g_uart_rx_interrupt,start,5) == 0){
		echo = 1;
	}else if(strncmp(g_uart_rx_interrupt,stop,4) == 0){
		echo = 0;
		memset((char*)g_uart_rx_interrupt,'\0',sizeof(g_uart_rx_interrupt)/sizeof(g_uart_rx_interrupt[0]));
		g_index = 0;
	}else if(strncmp(g_uart_rx_interrupt,ledon,6) == 0){
		g_led_on = char2int(&g_uart_rx_interrupt[6]);
	}else if(strncmp(g_uart_rx_interrupt,ledoff,7) == 0){
		g_led_off = char2int(&g_uart_rx_interrupt[7]);
	}
	echo_task();
}

