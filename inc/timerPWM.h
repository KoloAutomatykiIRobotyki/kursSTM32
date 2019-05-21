/*
 * timerPWM.h
 *
 *  Created on: 21.05.2019
 *      Author: Kuba
 */

#ifndef TIMERPWM_H_
#define TIMERPWM_H_

#define PWM_PIN GPIO_PIN_1
#define PWM_PORT GPIOA

TIM_HandleTypeDef myTimerPWM;
void initTimerPWM(void);

#endif /* TIMERPWM_H_ */
