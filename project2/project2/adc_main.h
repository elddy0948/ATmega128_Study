
/*
 * adc_main.h
 *
 * Created: 2023-11-20 오후 3:41:13
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _ADC_MAIN_H
#define _ADC_MAIN_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>

#define ADC_CLEAR_FLAG 0
#define TEMP_FLAG 1
#define VCC_FLAG 2
#define ADC_TEMP_COMPLETE_FLAG 11
#define ADC_VCC_COMPLETE_FLAG 21

uint8_t adc_flag;

ISR(ADC_vect);

void ADC_init(uint8_t flag, uint8_t target, uint8_t adfr);
void ADC_clear(void);
int ADC_get_value(float mul);

#endif
