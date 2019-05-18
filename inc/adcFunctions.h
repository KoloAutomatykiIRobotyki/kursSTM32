/*
 * adcFunctions.h
 *
 *  Created on: 13.05.2019
 *      Author: Kuba
 */

#ifndef ADCFUNCTIONS_H_
#define ADCFUNCTIONS_H_

extern int NUMBER_OF_ADC_CH;
extern uint16_t vectorAdc[1];
extern ADC_HandleTypeDef myAdc;        	// ADC1

void initADC(void);

#endif /* ADCFUNCTIONS_H_ */
