/*
 * adcFunctions.c
 *
 *  Created on: 13.05.2019
 *      Author: Kuba
 */
#include "stm32f1xx.h"
#include "adcFunctions.h"

int NUMBER_OF_ADC_CH = 1;
uint16_t vectorAdc[1];
ADC_HandleTypeDef myAdc;        	// ADC1

void initADC(void) {
	/*
	 * @brief configuration of ADC1 in DMA mode
	 * @param NUMBER_OF_ADC_CH, vectorAdc[]
	 * PB0 -AI - CH8 - 12 [MHz]
	 */
	// GPIO conf
	GPIO_InitTypeDef myAdcPin;
	myAdcPin.Pin = GPIO_PIN_0;
	myAdcPin.Mode = GPIO_MODE_ANALOG;
	myAdcPin.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &myAdcPin);

	// ADC1 conf
	__HAL_RCC_ADC1_CLK_ENABLE()
	;

	// RCC of ADC conf
	RCC_PeriphCLKInitTypeDef myAdcCLK;
	myAdcCLK.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	myAdcCLK.AdcClockSelection = RCC_ADCPCLK2_DIV6;    // 72/6=12 [MHz]
	HAL_RCCEx_PeriphCLKConfig(&myAdcCLK);

	myAdc.Instance = ADC1;
	myAdc.Init.ContinuousConvMode = ENABLE;
	myAdc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	myAdc.Init.DiscontinuousConvMode = DISABLE;
	myAdc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	myAdc.Init.NbrOfConversion = NUMBER_OF_ADC_CH;
	myAdc.Init.ScanConvMode = ADC_SCAN_ENABLE;
	HAL_ADC_Init(&myAdc);

	// ADC Channel conf
	ADC_ChannelConfTypeDef myAdcChanel;
	myAdcChanel.Channel = ADC_CHANNEL_8;
	myAdcChanel.Rank = ADC_REGULAR_RANK_1;
	myAdcChanel.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
	HAL_ADC_ConfigChannel(&myAdc, &myAdcChanel);

	// calibration
	HAL_ADCEx_Calibration_Start(&myAdc);

	// DMA1_CH1 conf
	__HAL_RCC_DMA1_CLK_ENABLE()
	;
	DMA_HandleTypeDef myDma;

	myDma.Instance = DMA1_Channel1;
	myDma.Init.Direction = DMA_PERIPH_TO_MEMORY;
	myDma.Init.PeriphInc = DMA_PINC_DISABLE;
	myDma.Init.MemInc = DMA_MINC_ENABLE;
	myDma.Init.MemDataAlignment = DMA_PDATAALIGN_HALFWORD;
	myDma.Init.PeriphDataAlignment = DMA_MDATAALIGN_HALFWORD;
	myDma.Init.Mode = DMA_CIRCULAR;
	myDma.Init.Priority = DMA_PRIORITY_HIGH;
	HAL_DMA_Init(&myDma);

	__HAL_LINKDMA(&myAdc, DMA_Handle, myDma);
	HAL_ADC_Start_DMA(&myAdc, (uint32_t*) vectorAdc, NUMBER_OF_ADC_CH);
}
