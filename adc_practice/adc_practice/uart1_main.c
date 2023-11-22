
/*
 * uart1_main.c
 *
 * Created: 2023-11-20 오전 8:43:34
 *  Author: HJ KIM
 */ 

#include "uart1_main.h"

void uart1_init(void)
{
	UBRR1H = 0x00;
	UBRR1L = 207;
	UCSR1A |= (1 << U2X1);
	UCSR1C |= 0x06;
	UCSR1B |= (1 << RXEN1);
	UCSR1B |= (1 << TXEN1);
}

void uart1_transmit(char data)
{
	while(!(UCSR1A & (1 << UDRE1)));
	UDR1 = data;
}

uint8_t uart1_receive(void)
{
	while(!(UCSR1A & (1 << RXC1)));
	return UDR1;
}

void uart1_print_string(char* str)
{
	for(int i = 0; str[i]; ++i)
		uart1_transmit(str[i]);
}

void uart1_print_1byte_number(uint8_t n)
{
	char numString[4] = "0";
	int i, index = 0;
	if(n > 0)
	{
		for (i = 0; n != 0; i++)
		{
			
			numString[i] = n % 10 + '0';
			n = n / 10;
		}
		numString[i] = '\0';
		index = i - 1;
	}
	for (i = index; i >= 0; i--)
		uart1_transmit(numString[i]);
}