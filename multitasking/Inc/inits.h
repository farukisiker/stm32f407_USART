#ifndef __INITS_H_
#define __INITS_H_
#include "SETBIT.h"
#include "stm32f407xx.h"
enum stop_bits{
	ONE,
	TWO
};
typedef enum stop_bits stop_bits;
enum data_length{
	EIGHT,
	NINE
};
typedef enum data_length data_length;
enum parity{
	NONE,
	EVEN,
	ODD
};
typedef enum parity parity;
struct nvic_usart{
	IRQn_Type irq;
	USART_TypeDef *uart_com;
};

struct uart_config{
	USART_TypeDef *uart_com;
	unsigned int baud_rate;
	data_length data_bits;
	parity parity;
	stop_bits stop_bits;
};
typedef struct uart_config uart_config;
typedef struct uart_nvic_config uart_nvic_config;

void SystemInit();
void GPIOD_13_O_Init();
void init_timers(void);
void init_Pwr_Voltage_Detector(void);
void init_uart(uart_config *uart);
void init_uart_interrupt(uart_config *uart);
#endif
