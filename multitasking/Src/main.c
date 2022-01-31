#include "main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

static void init_uart_main(){
	uart3.uart_com = USART3;
	uart3.baud_rate = 115200;
	uart3.data_bits = EIGHT;
	uart3.parity = NONE;
	uart3.stop_bits = ONE;
}
int main(void)
{
	init_Pwr_Voltage_Detector();//2.8V
	SystemInit();//heart beat init
	GPIOD_13_O_Init();//led for output
	init_timers();//tim7 at 1ms

	init_uart_main();//
	init_uart(&uart3);//start usart3
	init_uart_interrupt(&uart3);//start usart3 interrupt
    /* Loop forever */
	for(;;){
		parsing_task();
		led_drive(g_led_on,g_led_off);
	}
}
