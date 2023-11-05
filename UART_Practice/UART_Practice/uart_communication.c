
/*
 * uart_communication.c
 *
 * Created: 2023-11-05 오후 11:22:28
 *  Author: HJ KIM
 */ 

#include "uart_communication.h"

void UART1_init()
{
	UBRR1H = 0x00;
	UBRR1L = 207;
	
	UCSR1A |= _BV(U2X1);
	UCSR1C |= 0x06;
}

void UART1_transmit(char data)
{
	while(!(UCSR1A & (1 << UDRE1)));
	UDR1 = data;	
}

u8 UART1_receive()
{
	while(!(UCSR1A & (1 << RXC1)));
	return UDR1;
}

int UART_main()
{
	UART1_init();
	
	while (1)
	{
		UART1_transmit(UART1_receive());
	}
	return 0;
}