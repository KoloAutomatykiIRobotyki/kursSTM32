/*
 * clock.c
 *
 *  Created on: 18.05.2019
 *      Author: Kuba
 */
#include "stm32f1xx.h"
#include "clock.h"

void SystemClock_Config(void) {
	/**
	  * @brief inicialise clock
	  * @note set 72 [MHz]
	  */

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
