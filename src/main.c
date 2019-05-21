/**
 ******************************************************************************
 * @file    main.c
 * @author  Kuba Sondej scuba
 * @version V1.0
 * @date    09-April-2019
 * @brief   Default main function.
 * @desc    Program
 ******************************************************************************
 */

#include "stm32f1xx.h"
#include "clock.h"
#include "timer.h"
#include "uartFunctions.h"
#include "timerPWM.h"

volatile int fillLevel = 0;

char arrayOfReveivedChar[4] = { 0 };
char messageToSend[4] = "Kuba";

int main(void) {

	HAL_Init();                  // lib init
	SystemClock_Config();        // 72 MHz
	initUart();
	initTimer();
	initTimerPWM();
	HAL_UART_Receive_IT(&myUart, (uint8_t*) arrayOfReveivedChar, 4);
	__HAL_TIM_SET_COMPARE(&myTimerPWM, TIM_CHANNEL_2, 500);  //50[%]
	while (1) {

	}
}

void TIM4_IRQHandler(void) {
	HAL_TIM_IRQHandler(&myMainTimer);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/*
	 *
	 * kod do przerwania
	 *
	 * */


	if (fillLevel > 1000)
		fillLevel = 0;
	fillLevel += 50;
	__HAL_TIM_SET_COMPARE(&myTimerPWM, TIM_CHANNEL_2, (uint16_t)fillLevel);  //50[%]
	HAL_UART_Transmit_IT(&myUart, (uint8_t*) messageToSend, 4);
}

void USART2_IRQHandler(void) {
	HAL_UART_IRQHandler(&myUart);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	/*
	 * @brief in case of recivig data
	 *
	 */
	HAL_UART_Transmit_IT(&myUart, (uint8_t*) arrayOfReveivedChar, 4);
	HAL_UART_Receive_IT(&myUart, (uint8_t*) arrayOfReveivedChar, 4);

//	sprintf(Data, "Received message: %s\n\r", arrayOfReveivedChar);
//

}

