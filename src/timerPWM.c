/*
 * timerPWM.c
 *
 *  Created on: 21.05.2019
 *      Author: Kuba
 */
#include "stm32f1xx.h"
#include "timerPWM.h"

extern TIM_HandleTypeDef myTimerPWM;

void initTimerPWM(void) {
	/*
	 * GPIOA PA1 PWM2/2
	 * f=50[kHz]
	 */
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	GPIO_InitTypeDef myPinPWM;
	myPinPWM.Pin = PWM_PIN;
	myPinPWM.Mode = GPIO_MODE_AF_PP;
	myPinPWM.Speed = GPIO_SPEED_FREQ_HIGH;
	myPinPWM.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(PWM_PORT, &myPinPWM);

	__HAL_RCC_TIM2_CLK_ENABLE()
	;
	myTimerPWM.Instance = TIM2;
	myTimerPWM.Init.CounterMode = TIM_COUNTERMODE_UP;
	myTimerPWM.Init.Prescaler = 1440-1;
	myTimerPWM.Init.Period = 1000;
	myTimerPWM.Init.ClockDivision = 0;
	myTimerPWM.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	myTimerPWM.Init.RepetitionCounter = 0;
	HAL_TIM_PWM_Init(&myTimerPWM);

	TIM_OC_InitTypeDef myPWMchannel;
	myPWMchannel.OCMode = TIM_OCMODE_PWM1;         // 0 when overflow
	myPWMchannel.OCFastMode = TIM_OCFAST_ENABLE;   // 1 on start
	myPWMchannel.OCPolarity = TIM_OCPOLARITY_HIGH;
	myPWMchannel.OCNPolarity = TIM_OCNPOLARITY_LOW;
	myPWMchannel.OCIdleState = TIM_OCIDLESTATE_SET;
	myPWMchannel.OCNIdleState = TIM_OCNIDLESTATE_RESET;

	HAL_TIM_PWM_ConfigChannel(&myTimerPWM, &myPWMchannel, TIM_CHANNEL_2);

	HAL_TIM_PWM_Start(&myTimerPWM, TIM_CHANNEL_2);

}

