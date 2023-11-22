
/*
 * adc_main.c
 *
 * Created: 2023-11-20 오후 3:42:33
 *  Author: HJ KIM
 */ 

#include "adc_main.h"

static int adc_value = 0;

uint8_t ADC_FLAG_BIT = 0;
uint8_t AVCC_FLAG_BIT = 0;

uint8_t adc_flag = ADC_CLEAR_FLAG;

ISR(ADC_vect)
{
	cli();
	adc_value = (int)ADCL + ((int)ADCH << 8);
	if(adc_flag == TEMP_FLAG)
		adc_flag = ADC_TEMP_COMPLETE_FLAG;
	else if(adc_flag == VCC_FLAG)
		adc_flag = ADC_VCC_COMPLETE_FLAG;
	sei();
}

void ADC_init(uint8_t flag, uint8_t target, uint8_t adfr)
{
	adc_flag = flag;
	
	ADMUX |= target;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADIE);
	ADCSRA |= adfr;
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADSC);
}

void ADC_clear(void)
{
	ADMUX = 0x00;
	ADCSRA = 0x00;
}

int ADC_get_value(float mul)
{
	float float_value;
	int int_value;
	
	float_value = (float)adc_value * 5.0 / 1024.0;
	int_value = (int)(float_value * mul + 0.5);
	
	return int_value;
}
