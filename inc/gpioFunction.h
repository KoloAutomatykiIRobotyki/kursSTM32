/*
 * gpioFunction.h
 *
 *  Created on: 18.05.2019
 *      Author: Kuba
 */

#ifndef GPIOFUNCTION_H_
#define GPIOFUNCTION_H_

#define BUTTON_PIN GPIO_PIN_12
#define BUTTON_PORT GPIOA
#define LED_RED_PIN GPIO_PIN_13
#define LED_RED_PORT GPIOC

void initInputPins(void);
void initOutputPins(void);
void initInterruptsWithPins(void);
#endif /* GPIOFUNCTION_H_ */
