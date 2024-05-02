/*
 * bluetooth_practice.c
 *
 * Created: 2024-05-01 오후 10:08:27
 * Author : HoJoon
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"

int main(void)
{
	UART0_init();
    UART1_init();
	
	_delay_ms(500);
	
	UART1_print_string("AT");
	_delay_ms(1000);
	UART1_print_string("AT+NAMEHotmega");
	_delay_ms(1000);
	UART1_print_string("AT+PIN1234");
	_delay_ms(1000);
	UART1_print_string("AT+BAUD4");
	_delay_ms(1000);
	
    while (1)
    {
		UART0_transmit(UART1_receive());
    }
}

