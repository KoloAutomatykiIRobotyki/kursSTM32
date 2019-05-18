//#include "stm32f1xx.h"
//
//int main(void) {
//
//	HAL_Init();                  // inicjalizacja biblioteki
//	__HAL_RCC_GPIOD_CLK_ENABLE();
//	GPIO_InitTypeDef mojPin;
//	mojPin.Pin = GPIO_PIN_All;
//	mojPin.Mode = GPIO_MODE_OUTPUT_PP;
//	mojPin.Pull = GPIO_PULLUP;
//	mojPin.Speed = GPIO_SPEED_FREQ_MEDIUM;
//	HAL_GPIO_Init(GPIOD, &mojPin);
//
//
//	while(1)
//		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_All,1);
//}

//UART POLLING  MODE
/**
 ******************************************************************************
 * @file    main.c
 * @author  Kuba Sondej scuba
 * @version V1.0
 * @date    09-April-2019
 * @brief   Default main function.
 * @desc    Program nr 2
 ******************************************************************************
 */

#include "stm32f1xx.h"
#include <math.h>
#include <stdlib.h>
#include "uartFunctions.h"


void setParameters(void);
void setParameters(void);
void readChar(void);
void sendChar(char c);
int __io_putchar(int z);
int a, b, c;
int main(void) {

	HAL_Init();                  // inicjalizacja biblioteki
	SystemClock_Config();        // takowanie 72 [MHz]
	initUartPins();
	initUart();

	setParameters();
	while (1) {
		readChar();
	}
}
void readChar(void) {
	if (__HAL_UART_GET_FLAG(&myUart, UART_FLAG_RXNE)) {
		uint8_t c;
		int a;
		char array[5] = { 0 };
		HAL_UART_Receive(&myUart, &c, 1, 10);
		switch (c) {
		case 'd':
			printf("Ustawiasz parametry... \nCzekaj...\n\n");
			HAL_Delay(1000);
			setParameters();
			break;
		case 'z':
			printf(
					"Konczysz dzialanie aplikacji -\nkliknij reset by zaczac na nowo \n\n");
			exit(1);
		default:
			printf("Wyslales cos: %c \n", c);
			HAL_Delay(1000);
//			array[0]=c;
//			sscanf(array,"%d",&a);
//			printf("2*a=%d\n",2*a);
			HAL_Delay(1000);
		}
	}
}

void sendChar(char c) {
	// typ void
	// param @c - char
	HAL_UART_Transmit(&myUart, (uint8_t*) &c, 1, 10);
}
int __io_putchar(int z) {
	if (z == '\n')
		sendChar('\r');
	sendChar(z);
	return z;
}

void setParameters(void) {
	char myChar;                    // znak do odebrania
	char myArray[10] = { 0 };           // tablica znaków
	int i = 0, where = 0;               // zmienne do nawigacji
	printf("Witaj w programie! \n");
	printf("Podaj wektor liczb calkowitych w postaci: [a; b; c] \n");
	while (myChar != ']')  // podawaj dopuki nie dobijemy do zancznika koñca ']'
		if (__HAL_UART_GET_FLAG(&myUart, UART_FLAG_RXNE)) {
			HAL_UART_Receive(&myUart, (uint8_t*) &myChar, 1, 10); // odbieramy dane
			myArray[i] = myChar;                   // zapisanie zanku do tablicy
			where = i;                                  // lokalizujemy znak ']'
			i++;                                          // do nastêpnego znaku
		}
	//pozbycie siê zerowego(']') i ostatniego znaku (']') na pozycji 0 oraz where
	myArray[0] = ' ';
	myArray[where] = ' ';
	// przypisanie zmiennych
	sscanf(myArray, "%d;%d;%d", &a, &b, &c); // a b c - zmienne globalne typu int
	printf("\nWysylam dane: \na=%d \nb=%d \nc=%d\n", a, b, c);
	printf("Wysy³am dane do 3 potegi: \na=%d \nb=%d \nc=%d\n", a * a * a,
			b * b * b, c * c * c);
	printf(
			"\nJak chcesz ponownie wyslac dane kliknij 'd' oraz 'z' aby zamknac\n\n");
}

//********************************************************************************

//#include "stm32f1xx.h"
//#include <stdio.h>
//#include <stdlib.h>
//
//void uart_pin_init(void);
//
//void SystemClock_Config(void);
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
//UART_HandleTypeDef myUart;		// UART2
//
//uint8_t byte;
//uint8_t Received;
//
//int main(void) {
//	int i = 0;
//
//	HAL_Init();
//	SystemClock_Config();
//	uart_pin_init();
//	//HAL_UART_Receive_IT(&myUart, &byte, 1);
//	//HAL_UART_Receive_IT(&myUart, Received, 10);
//	HAL_UART_Transmit_IT(&myUart, (uint8_t*) &Received,1);
//	while (1) {
//	}
//}
//
//void USART2_IRQHandler(void) {
//	HAL_UART_IRQHandler(&myUart);
//}
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//
//	char Data[40]; // Tablica przechowujaca wysylana wiadomosc.
//
//	sprintf(Data, "Odebrana wiadomosc: %s\n\r", Received);
//
//	HAL_UART_Transmit_IT(&myUart, (uint8_t*) Data, 1); // Rozpoczecie nadawania danych z wykorzystaniem przerwan
//	HAL_UART_Receive_IT(&myUart, &Received, 1); // Ponowne w³¹czenie nas³uchiwania
//
//}
////void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
////	if (huart->Instance == USART2) {
////		//Transmit one byte with 100 ms timeout
////		HAL_UART_Transmit(&myUart, &byte, 1, 100);
////
////		// Receive one byte in interrupt mode
////		HAL_UART_Receive_IT(&myUart, &byte, 1);
////	}
////}
//
//void uart_pin_init(void) {
//	// Funkcja konfiguracyjna komunikacje z komputerem
//
//	__HAL_RCC_GPIOA_CLK_ENABLE()
//	;
//	__HAL_RCC_USART2_CLK_ENABLE()
//	;
//
//	GPIO_InitTypeDef myUartPin;
//	myUartPin.Pin = GPIO_PIN_2 | GPIO_PIN_3; // 2 linia TX wysy³anie PA2 nie jest scrossowane
//	myUartPin.Mode = GPIO_MODE_AF_PP;
//	myUartPin.Pull = GPIO_NOPULL;
//	myUartPin.Speed = GPIO_SPEED_FREQ_HIGH;
//	HAL_GPIO_Init(GPIOA, &myUartPin);
//
//	myUartPin.Pin = GPIO_PIN_3;
//	myUartPin.Mode = GPIO_MODE_AF_INPUT; // 3 linia RX odbieranie PA3 nie jest scrossowane
//	myUartPin.Pull = GPIO_NOPULL;
//	myUartPin.Speed = GPIO_SPEED_FREQ_HIGH;
//	HAL_GPIO_Init(GPIOA, &myUartPin);
//
//	myUart.Instance = USART2;
//	myUart.Init.BaudRate = 115200;                     // prêdkosc transmisji
//	myUart.Init.WordLength = UART_WORDLENGTH_8B;       // d³ugoœc
//	myUart.Init.Parity = UART_PARITY_NONE;             // parzystoœc
//	myUart.Init.StopBits = UART_STOPBITS_1;            // bity stopu
//	myUart.Init.OverSampling = UART_OVERSAMPLING_16;   //
//	myUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//	myUart.Init.Mode = UART_MODE_TX_RX;
//	HAL_UART_Init(&myUart);
//
//	// Peripheral interrupt init
//	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(USART2_IRQn);
//	__HAL_UART_ENABLE_IT(&myUart, UART_IT_RXNE); // flag receive
//	__HAL_UART_ENABLE_IT(&myUart, UART_IT_TC); // flat Tx_IT
//}
//
////---------------------------KONFIGURACJA ZEGARA---------------------------------
//void SystemClock_Config(void) {
//	RCC_ClkInitTypeDef clkinitstruct = { 0 };
//	RCC_OscInitTypeDef oscinitstruct = { 0 };
//
//	oscinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//	oscinitstruct.HSEState = RCC_HSE_ON;
//	oscinitstruct.HSIState = RCC_HSI_OFF;
//	oscinitstruct.PLL.PLLState = RCC_PLL_ON;
//	oscinitstruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//	oscinitstruct.PLL.PLLMUL = RCC_PLL_MUL9;
//	if (HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
//		while (1)
//			;
//
//	clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
//	RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
//	clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//	clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//	clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
//	clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
//	if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2) != HAL_OK)
//		while (1)
//			;
//
//}
//////////////////////////////////////////////////////////////////////////////////

