/*
 * uartFunctions.h
 *
 *  Created on: 07.05.2019
 *      Author: Kuba
 */

#ifndef UARTFUNCTIONS_H_
#define UARTFUNCTIONS_H_

UART_HandleTypeDef myUart;

void initUartPins(void);
void initUart(void);
void SystemClock_Config(void);

#endif /* UARTFUNCTIONS_H_ */
