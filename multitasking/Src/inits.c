
#include "stm32f407xx.h"
#include "inits.h"
#define USART_1_PLL_CLK 84000000.0f
#define USART_2_3_PLL_CLK 42000000.0f

void init_uart_interrupt(uart_config *uart){
	NVIC_EnableIRQ(USART3_IRQn);
	SET_BIT(uart->uart_com->CR1, USART_CR1_RXNEIE);//transmit buffer empty interrupt
}

static uint32_t baudrate_calc(int baud,uart_config *uart){
	float temp1;
	if(uart->uart_com == USART1)
		temp1 = ( USART_1_PLL_CLK / baud) / 16 ;
	else
		temp1 = ( USART_2_3_PLL_CLK / baud) / 16 ;

	int int_part = (int)temp1;
	float floating_part = temp1 - (float)int_part;
	int float2int = (int)(floating_part * 16.0f);

	return ((int_part<<4U) | float2int);
}

void init_uart(uart_config *uart){
	int uart_case = 0;
	if(uart->uart_com == USART1) uart_case = 1;
	if(uart->uart_com == USART2) uart_case = 2;
	if(uart->uart_com == USART3) uart_case = 3;
	switch (uart_case) {
		case 1:
			SET_BIT(RCC->APB2ENR,RCC_APB2ENR_USART1EN);
			SET_BIT(RCC->APB2RSTR,RCC_APB2RSTR_USART1RST);
			SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOAEN);
			MODIFY_REG(GPIOA->AFR[1],(0xFU<<4U),(7U<<4U));//PA9
			MODIFY_REG(GPIOA->AFR[1],(0xFU<<8U),(7U<<8U));//PA10
			MODIFY_REG(GPIOA->MODER,GPIO_MODER_MODER9_Msk,GPIO_MODER_MODE9_1);//AF7,USART1
			MODIFY_REG(GPIOA->MODER,GPIO_MODER_MODER10_Msk,GPIO_MODER_MODE10_1);//AF7,USART1
			MODIFY_REG(GPIOA->PUPDR,GPIO_PUPDR_PUPD9_Msk,0x0U);//no pp
			MODIFY_REG(GPIOA->PUPDR,GPIO_PUPDR_PUPD10_Msk,0x0U);//no pp
			CLEAR_BIT(RCC->APB2RSTR,RCC_APB2RSTR_USART1RST);
			break;
		case 2:
			SET_BIT(RCC->APB1ENR,RCC_APB1ENR_USART2EN);
			SET_BIT(RCC->APB1RSTR,RCC_APB1RSTR_USART2RST);
			SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIODEN);
			MODIFY_REG(GPIOD->AFR[0],(0xFU<<20U),(7U<<20U));//PD5
			MODIFY_REG(GPIOD->AFR[0],(0xFU<<20U),(7U<<20U));//PD6
			MODIFY_REG(GPIOD->MODER,GPIO_MODER_MODER5_Msk,GPIO_MODER_MODE5_1);//AF7,USART2
			MODIFY_REG(GPIOD->MODER,GPIO_MODER_MODER6_Msk,GPIO_MODER_MODE6_1);//AF7,USART2
			MODIFY_REG(GPIOD->PUPDR,GPIO_PUPDR_PUPD5_Msk,0x0U);//no pp
			MODIFY_REG(GPIOD->PUPDR,GPIO_PUPDR_PUPD6_Msk,0x0U);//no pp
			CLEAR_BIT(RCC->APB1RSTR,RCC_APB1RSTR_USART2RST);
			break;
		case 3:
			SET_BIT(RCC->APB1ENR,RCC_APB1ENR_USART3EN);
			SET_BIT(RCC->APB1RSTR,RCC_APB1RSTR_USART3RST);
			SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOCEN);
			MODIFY_REG(GPIOC->AFR[1],(0xFU<<12U),(7U<<12U));//
			MODIFY_REG(GPIOC->AFR[1],(0xFU<<8U),(7U<<8U));//
			MODIFY_REG(GPIOC->MODER,GPIO_MODER_MODER11_Msk,GPIO_MODER_MODE11_1);//AF7,USART1
			MODIFY_REG(GPIOC->MODER,GPIO_MODER_MODER10_Msk,GPIO_MODER_MODE10_1);//AF7,USART1
			MODIFY_REG(GPIOC->PUPDR,GPIO_PUPDR_PUPD11_Msk,0x0U);//no pp
			MODIFY_REG(GPIOC->PUPDR,GPIO_PUPDR_PUPD10_Msk,0x0U);//no pp
			CLEAR_BIT(RCC->APB1RSTR,RCC_APB1RSTR_USART3RST);
			break;
		default:
			break;
	}
	/*
	 * Tx / Rx baud rate = fPCLKx / (16 * USARTDIV);
	 */
	uart->uart_com->BRR = baudrate_calc(uart->baud_rate,uart);
	//uart->uart_com->SR &=~0X03FF;

	MODIFY_REG(uart->uart_com->CR1,USART_CR1_UE_Msk,USART_CR1_UE);//usart enable
	if(uart->data_bits == EIGHT)	MODIFY_REG(uart->uart_com->CR1,USART_CR1_M_Msk,0U); //word length
	else if(uart->data_bits == NINE)	MODIFY_REG(uart->uart_com->CR1,USART_CR1_M_Msk,USART_CR1_M);// word length

	if(uart->parity == NONE)	CLEAR_BIT(uart->uart_com->CR1,USART_CR1_PCE);
	else{
		SET_BIT(uart->uart_com->CR1,USART_CR1_PCE);
		if(uart->parity == EVEN)	MODIFY_REG(uart->uart_com->CR1, USART_CR1_PS_Msk, 0); //even parity
		else if(uart->parity == ODD)	MODIFY_REG(uart->uart_com->CR1, USART_CR1_PS_Msk, USART_CR1_PS); //odd parity
	}
	if(uart->stop_bits == ONE) MODIFY_REG(uart->uart_com->CR2, USART_CR2_STOP_Msk,USART_CR2_STOP_0);// stop bit 1
	else if(uart->stop_bits == TWO) MODIFY_REG(uart->uart_com->CR2, USART_CR2_STOP_Msk,USART_CR2_STOP_1);//stop bit 2

	MODIFY_REG(uart->uart_com->CR1 , USART_CR1_RE_Msk, USART_CR1_RE);//receiver is enabled
	/*
	 * interrupt
	 */
}

void init_Pwr_Voltage_Detector(void){
	PWR->CR |= 0xC0UL;	//110 selected for 2.8V selected as threshold
	PWR->CR |= PWR_CR_PVDE;	//Enable Detector
}
void init_timers(void)   ///
{
    RCC->APB1ENR|=0x00000020;            // timer7 is 84Mhz
    TIM7->CR1=0x0080;                  // Otomatic Reload
    TIM7->PSC=42000-1;                      // Prescaler 21000, Count freq = fCK_PSC / (loadval + 1) = 84E6 / (21000) =   2KHz (0.5ms)
    TIM7->ARR =1;                   // counter is counting 2 (1ms)
    TIM7->DIER=0x0001;                 // Update Int enable
    NVIC->ISER[1] |= 0X00800000;        // NVIC Timer 7 interrup is enabled
    TIM7->CR1|=0x0001;                 // Counter Enable
}

void GPIOD_13_O_Init(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	/*
	 * output PD13, USER LED
	 */
	MODIFY_REG(GPIOD->MODER,GPIO_MODER_MODER13_Msk,GPIO_MODER_MODER13_0);//d13
	//output type is push pull
	CLEAR_BIT(GPIOD->OTYPER,GPIO_OTYPER_OT13_Msk);
	//out-speed is high speed
	MODIFY_REG(GPIOD->OSPEEDR,GPIO_OSPEEDR_OSPEED13_Msk,GPIO_OSPEEDR_OSPEED13_Msk);
	//No pull up, no pull down
	MODIFY_REG(GPIOD->PUPDR,0x3UL<<13UL,0x0UL);
}

void SystemInit(){ //clock config
	unsigned int i;

	for(i=0;i<0x00100000;i++);     //
	(*((int*)0xE000ED88))|=0x00F00000;  //floating point
	//RCC->CFGR |= 0x00009400;      // AHB & APB max freq
	RCC->CFGR |= 0x30009400;        // mco2 sysclk/4
	RCC->CR |= 0x00010000;        // HSE Xtal osc
	while (!(RCC->CR & 0x00020000));  // Xtal osc stable
	RCC->PLLCFGR = 0x07405408;      //PLL  M=8, N=336, P=2  Q=7
	//RCC->PLLCFGR = 0x0740540C;   //PLL  M=12, N=336, P=2 ve Q=7
	//RCC->PLLCFGR = 0x0700540F;      //PLL  M=16, N=336, P=2  Q=7  ,HSI pll
	RCC->CR |= 0x01000000;          //PLL  enabled
	while(!(RCC->CR & 0x02000000));   //wait pll till ready
	FLASH->ACR = 0x00000705;        //page 55
	RCC->CFGR |= 0x00000002;        //System Clk is fed from PLL

	while ((RCC->CFGR & 0x0000000F) != 0x0000000A); // wait till feed
}
