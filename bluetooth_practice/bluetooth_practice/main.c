/*
 * bluetooth_practice.c
 *
 * Created: 2024-05-01 오후 10:08:27
 * Author : HoJoon
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "UART1.h"

int main(void)
{
    UART1_init();
	
	_delay_ms(500);
	
    while (1) 
    {
		UART1_print_string("AT");
		
		_delay_ms(1000);
		
		UART1_print_string("AT+NAMEAtmega128Blue");
		
		_delay_ms(1000);
		
		UART1_print_string("AT+PIN1234");
		
		_delay_ms(1000);
		
		UART1_print_string("AT+BAUD4");
    }
}

