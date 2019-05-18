/*
 * uartFunctions.c
 *
 *  Created on: 07.05.2019
 *      Author: Kuba
 */
#include "stm32f1xx.h"
#include "uartFunctions.h"

void initUartPins(void) {
	// Uniwersalna funkcja inicjalizuj¹ca piny do modu³u UART2
	// TX -> PA2
	// RX -> PA3

	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	GPIO_InitTypeDef myUartGpioPin;

	// linia TX wysy³anie PA2
	myUartGpioPin.Pin = GPIO_PIN_2;
	myUartGpioPin.Mode = GPIO_MODE_AF_PP;
	myUartGpioPin.Pull = GPIO_NOPULL;
	myUartGpioPin.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &myUartGpioPin);

	// linia RX odbieranie PA3
	myUartGpioPin.Pin = GPIO_PIN_3;
	myUartGpioPin.Mode = GPIO_MODE_AF_INPUT;
	myUartGpioPin.Pull = GPIO_NOPULL;
	myUartGpioPin.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &myUartGpioPin);
}

void initUart(void) {
	// konfiguracja modu³u UART2
	// tryb blokuj¹cy
	// FULL DUPLEX

	__HAL_RCC_USART2_CLK_ENABLE()
	;

	myUart.Instance = USART2;
	myUart.Init.BaudRate = 115200;        // prêdkoœc transmisji
	myUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	myUart.Init.Mode = UART_MODE_TX_RX;  // wysy³anie i odbieranie
	myUart.Init.OverSampling = UART_OVERSAMPLING_16;
	myUart.Init.Parity = UART_PARITY_NONE;
	myUart.Init.StopBits = UART_STOPBITS_1;
	myUart.Init.WordLength = UART_WORDLENGTH_8B;

	HAL_UART_Init(&myUart);
}





// KONFIGURACJA ZEGARA -----------------------------------
void SystemClock_Config(void) {
	RCC_ClkInitTypeDef clkinitstruct = { 0 };
	RCC_OscInitTypeDef oscinitstruct = { 0 };
	oscinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscinitstruct.HSEState = RCC_HSE_ON;
	oscinitstruct.HSIState = RCC_HSI_OFF;
	oscinitstruct.PLL.PLLState = RCC_PLL_ON;
	oscinitstruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	oscinitstruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
		while (1)
			;
	clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK |
	RCC_CLOCKTYPE_HCLK |
	RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
	clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2) != HAL_OK)
		while (1)
			;
}
