/*
 * adc_practice.c
 *
 * Created: 2023-11-19 오후 11:26:49
 * Author : HJ KIM
 */ 

#include "thermistor_example.h"

int main(void)
{
    init_ports();
	init_timer();
	init_adc();
	
	sei();
	
    while (1) 
    {
		display_adc(ad_val);
		_delay_ms(2);
    }
	
	return 0;
}

