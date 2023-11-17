
/*
 * receive_example.c
 *
 * Created: 2023-11-17 오후 12:40:33
 *  Author: HJ KIM
 */ 


#include "receive_example.h"

unsigned char seg_pat[16]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d,
0x07,0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
uint8_t numbers[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
uint8_t num = 0;
uint8_t rd = 0;

void init_ports(void)
{
	DDRB |= 0xF0;
	DDRD |= 0xF0;
	DDRG |= 0x0F;
	
	PORTB = 0x00;
	PORTD = 0x00;
	PORTG = 0x08; 
}

void init_uart1(void)
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	
	UBRR0H = BAUD_RATE_H;
	UBRR0L = BAUD_RATE_L;
}

void uart1_main()
{
	while((UCSR0A & 0x80) == 0x00)
	{
		PORTD = ((seg_pat[num] & 0x0F) << 4) | (PORTD & 0x0F);
		PORTB = (seg_pat[num] & 0x70) | (PORTB & 0x0F);
	}
	
	rd = UDR0;
	
	if (rd >= '0' && rd <= '9') num = rd - '0';
	else if (rd >= 'a' && rd <= 'f') num = rd - 'a' + 10;
	else if (rd >= 'A' && rd <= 'F') num = rd - 'A' + 10;
}