
/*
 * serial_test.c
 *
 * Created: 2023-11-02 오후 9:22:35
 *  Author: HJ KIM
 */ 

#define F_CPU 16000000L
#define _BV(bit) (1 << (bit))

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void UART0_init(void);
void UART0_transmit(char data);

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

void UART0_init(void)
{
	UBRR0H = 0x00; // 9.600 보율로 설정
	UBRR0L = 207;
	
	UCSR0A |= _BV(U2X0);
	UCSR0C |= 0x06;
	
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);
}

void UART0_transmit(char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

int serial_connection_test()
{
	UART0_init();
	stdout = &OUTPUT;
	unsigned int count;
	
	while(1) 
	{
		printf("%d\n\r", count++);
		_delay_ms(1000);
	}
	
	return 0;
}
