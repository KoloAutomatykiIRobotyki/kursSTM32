/*
 * gpioFunction.c
 *
 *  Created on: 18.05.2019
 *      Author: Kuba
 */
#include "stm32f1xx.h"
#include "gpioFunction.h"



void initInputPins(void){
	/*
	 * @brief set BUTTON as a input
	 *
	 */

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef myButton;

	myButton.Pin = BUTTON_PIN;              // set pin
	myButton.Mode = GPIO_MODE_INPUT;        // kind of input
	myButton.Pull = GPIO_PULLUP;            // pullup resistor
	myButton.Speed = GPIO_SPEED_FREQ_LOW;   // speed of pin propagation

	HAL_GPIO_Init(BUTTON_PORT, &myButton);
}


void initOutputPins(void) {
	/*
	 * @brief set the LED_RED output
	 *
	 */

	// 1) Clock
	__HAL_RCC_GPIOA_CLK_ENABLE();
	// 2) Declare of var
	GPIO_InitTypeDef myLed;
	// 3) Fill the fields
	myLed.Pin = LED_RED_PIN;             // set pin
	myLed.Mode = GPIO_MODE_OUTPUT_PP;    // kind of output
	myLed.Pull = GPIO_NOPULL;            // no pullup resistors
	myLed.Speed = GPIO_SPEED_FREQ_LOW;   // speed of pin propagation
	// 4) Init
	HAL_GPIO_Init(LED_RED_PORT, &myLed);
}

void initInterruptsWithPins(void){
	/*
	 * @brief interrupts
	 *
	 *
	 */

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef myButton;

	myButton.Pin = GPIO_PIN_11;
	myButton.Mode = GPIO_MODE_IT_RISING;    // On rising edge
	myButton.Pull = GPIO_PULLUP;
	myButton.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &myButton);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn,0,0); // set priority
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);       // enable of interrupts

}

//void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin){
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
//}

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
//	/*
//	 * Set the code here...
//	 *
//	 */
//}
