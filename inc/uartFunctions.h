/*
 * uartFunctions.h
 *
 *  Created on: 07.05.2019
 *      Author: Kuba
 */

#ifndef UARTFUNCTIONS_H_
#define UARTFUNCTIONS_H_

UART_HandleTypeDef myUart;

void initUart(void);
void readChar(void);
int __io_putchar(int z);
int * setParameters(void);

#endif /* UARTFUNCTIONS_H_ */
