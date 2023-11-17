
/*
 * basic_uart.c
 *
 * Created: 2023-11-16 오후 10:43:14
 *  Author: HJ KIM
 */ 

#include "basic_uart.h"

uint8_t TX_COMPLETE_FLAG_BIT = 1;
uint8_t RX_COMPLETE_FLAG_BIT = 1;
uint8_t DATA_REGISTER_EMPTY_FLAG_BIT = 1;

ISR(USART1_RX_vect)
{
	cli();
	PORTC = 0xFE;
	RX_COMPLETE_FLAG_BIT = 1;
	sei();
}

ISR(USART1_TX_vect)
{
	cli();
	TX_COMPLETE_FLAG_BIT = 1;
	sei();
}

ISR(USART1_UDRE_vect)
{
	cli();
	DATA_REGISTER_EMPTY_FLAG_BIT = 1;
	sei();
}

void uart1_init(void)
{
	DDRC |= 0xFF;
	PORTC = 0xFF;
	// setup baud rate
	// datasheet p.266
	UBRR1H = 0x00;			// baud rate : 9,600
	UBRR1L = 0xCF;			// 207
	UCSR1A |= (1 << U2X1);	// DOUBLE THE UART TRANSMISSION SPEED
	
	UCSR1B |= (1 << TXEN1);	// ENABLE TRANSMITTER
	UCSR1B |= (1 << RXEN1);	// ENABLE RECEIVER
	
	UCSR1C |= (1 << UCSZ11);	// set character size 8-bit
	UCSR1C |= (1 << UCSZ10);

}

void uart1_interrupt_init(void)
{
	UCSR1B |= (1 << RXCIE1);	// RX COMPLETE INTERRUPT ENABLE
	UCSR1B |= (1 << TXCIE1);	// TX COMPLETE INTERRUPT ENABLE
	UCSR1B |= (1 << UDRIE1);	// DATA REGISTER EMPTY INTERRUPT ENABLE
}

void uart1_transmit(uint8_t data)
{
	while(!DATA_REGISTER_EMPTY_FLAG_BIT);
	DATA_REGISTER_EMPTY_FLAG_BIT = 0;
	UDR1 = data;
}

uint8_t uart1_receive(void)
{
	while(!RX_COMPLETE_FLAG_BIT);
	RX_COMPLETE_FLAG_BIT = 0;
	return UDR1;
}

void uart1_print_string(char *str)
{
	int i;
	for (i = 0; str[i]; i++)
	{
		uart1_transmit(str[i]);
	}
}