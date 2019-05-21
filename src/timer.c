/*
 * timer.c
 *
 *  Created on: 20.05.2019
 *      Author: Kuba
 */
#include "stm32f1xx.h"
#include "timer.h"

extern TIM_HandleTypeDef myMainTimer;
void initTimer(void) {
	/* TIM4
	 * f=2 [Hz]
	 * */
	__HAL_RCC_TIM4_CLK_ENABLE()
	;
	myMainTimer.Instance = TIM4;
	myMainTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
	myMainTimer.Init.Prescaler = 36000 - 1;
	myMainTimer.Init.Period = 1000 - 1;
	myMainTimer.Init.ClockDivision = 0;
	myMainTimer.Init.AutoReloadPreload=TIM_AUTOMATICOUTPUT_DISABLE;
	myMainTimer.Init.RepetitionCounter=0;
	HAL_TIM_Base_Init(&myMainTimer);

	HAL_NVIC_SetPriority(TIM4_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);

	HAL_TIM_Base_Start_IT(&myMainTimer);

}

