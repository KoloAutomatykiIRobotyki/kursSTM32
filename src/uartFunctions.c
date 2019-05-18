/*
 * uartFunctions.c
 *
 *  Created on: 07.05.2019
 *      Author: Kuba
 */
#include "stm32f1xx.h"
#include <stdlib.h>
#include "uartFunctions.h"

extern UART_HandleTypeDef myUart;

void initUart(void) {
	/*
	 * @brief polling mode
	 * @note
	 * UART2 configuration
	 * TX ----> PA2
	 * RX ----> PA3
	 * @param baudRate = 115200
	 */
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;

	GPIO_InitTypeDef myUartGpioPin;

	// TX ---> PA2
	myUartGpioPin.Pin = GPIO_PIN_2;
	myUartGpioPin.Mode = GPIO_MODE_AF_PP;
	myUartGpioPin.Pull = GPIO_NOPULL;
	myUartGpioPin.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &myUartGpioPin);

	// RX ---> PA3
	myUartGpioPin.Pin = GPIO_PIN_3;
	myUartGpioPin.Mode = GPIO_MODE_AF_INPUT;
	myUartGpioPin.Pull = GPIO_NOPULL;
	myUartGpioPin.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &myUartGpioPin);

	// UART2
	__HAL_RCC_USART2_CLK_ENABLE()
	;

	myUart.Instance = USART2;
	myUart.Init.BaudRate = 115200;
	myUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	myUart.Init.Mode = UART_MODE_TX_RX;
	myUart.Init.OverSampling = UART_OVERSAMPLING_16;
	myUart.Init.Parity = UART_PARITY_NONE;
	myUart.Init.StopBits = UART_STOPBITS_1;
	myUart.Init.WordLength = UART_WORDLENGTH_8B;

	HAL_UART_Init(&myUart);

	// interrupt mode:
	// uncomment

//	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(USART2_IRQn);
}
//------------------------------------------------------------------------
// Polling mode - functions:

int __io_putchar(int z) {
	/*
	 * @brief to sending by printf function
	 */
	HAL_UART_Transmit(&myUart, (uint8_t*) &z, 1, 10);
	return z;
}

void readChar(void) {
	/**
	 * @brief reciving data from uart polling mode
	 *
	 */
	if (__HAL_UART_GET_FLAG(&myUart, UART_FLAG_RXNE)) {
		uint8_t c;
		int a;
		HAL_UART_Receive(&myUart, &c, 1, 10);
		switch (c) {
		case 'd':
			printf("Sent d... \nWait...\n\n");
			HAL_Delay(1000);
			break;
		case 'z':
			printf("Exit -\npress reset to continue... \n\n");
			exit(1);
		default:
			printf("Sent sth looks like: %c \n", c);
			HAL_Delay(1000);
		}
	}
}

int * setParameters(void) {
	/**
	 * @brief setting parameters for 1st code execution
	 * @return function return pointer to vector of 3 int vectorOfParam
	 */

	char myChar;                        // char to receive
	char myArray[10] = { 0 };           // array of chars
	int i = 0, where = 0;               // var to navigate
	int vectorOfParam[3] = { 0 };           // vector to return
	printf("Hello! \n");
	printf("Write vector of int numbers which look like: [a; b; c] \n");

	while (myChar != ']')               // end of data frame ']'
		if (__HAL_UART_GET_FLAG(&myUart, UART_FLAG_RXNE)) {
			HAL_UART_Receive(&myUart, (uint8_t*) &myChar, 1, 10);
			myArray[i] = myChar;
			where = i;                  // looking for poz of char ']'
			i++;
		}
	// get rid of '[' and last char ']' on poz 0 and where
	myArray[0] = ' ';
	myArray[where] = ' ';

	// assign var
	sscanf(myArray, "%d;%d;%d", &vectorOfParam[0], &vectorOfParam[1],
			&vectorOfParam[2]);
	printf("\nI received: \na=%d \nb=%d \nc=%d\n", *(vectorOfParam),
			*(vectorOfParam + 1), *(vectorOfParam + 2));
	printf("\nThat is all.. See you!\n\n");

	return vectorOfParam;
}

//----------------------------------------------------------------------
// Interrupt mode
// it is needed to copy into main file
//void USART2_IRQHandler(void) {
//	HAL_UART_IRQHandler(&myUart);
//}

//HAL_UART_Receive_IT(&myUart, arrayOfReveivedChar, 10);
//HAL_UART_Transmit_IT(&myUart, (uint8_t*) messageToSend,10);
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
/*
 * @brief in case of recivig data
 *
 */
//	sprintf(Data, "Received message: %s\n\r", arrayOfReveivedChar);
//

//
//}
