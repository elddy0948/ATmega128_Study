/*
 * adc_practice.c
 *
 * Created: 2023-11-19 오후 11:26:49
 * Author : HJ KIM
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

void ADC_init(uint8_t channel)
{
	ADMUX |= (1 << REFS0);
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADFR);
	ADMUX |= ((ADMUX & 0xE0) | channel);
	ADCSRA |= (1 << ADSC);
}

int read_ADC(void)
{
	while(!(ADCSRA & (1 << ADIF)));
	return ADC;
}

int main(void)
{
    int read;
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART1_init();
	ADC_init(0);
	
    while (1) 
    {
		read = read_ADC();
		printf("%d\r\n", read);
		_delay_ms(1000);
    }
	
	return 0;
}

