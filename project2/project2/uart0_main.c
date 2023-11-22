
/*
 * uart0_main.c
 *
 * Created: 2023-11-17 오후 2:06:25
 *  Author: HJ KIM
 */ 
#include "uart0_main.h"

const char* menu_description =
	"EXTERNAL INTERRUPT MENU\rEXTERNAL INTERRUPT 4 (type 4) \rEXTERNAL INTERRUPT 5 (type 5) \rEXTERNAL INTERRUPT 6 (type 6) \rEXTERNAL INTERRUPT 7 (type 7) \rENTER : ";

uint8_t UART0_RX_FLAG_BIT = 0;
uint8_t EINT4_ENABLE_FLAG_BIT = 0;
uint8_t EINT5_ENABLE_FLAG_BIT = 0;
uint8_t EINT6_ENABLE_FLAG_BIT = 0;
uint8_t EINT7_ENABLE_FLAG_BIT = 0;
uint8_t data = 0;

ISR(USART0_RX_vect)
{
	cli();

	UART0_RX_FLAG_BIT = 1;
	data = UDR0;
	switch(data)
	{
		case '4':
		EINT4_ENABLE_FLAG_BIT = 1;
		break;
		case '5':
		EINT5_ENABLE_FLAG_BIT = 1;
		break;
		case '6':
		EINT6_ENABLE_FLAG_BIT = 1;
		break;
		case '7':
		EINT7_ENABLE_FLAG_BIT = 1;
		break;
		default:
		break;
	}
	
	sei();
}

void UART0_init()
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0B |= (1 << RXCIE0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	
	UBRR0H = BAUD_RATE_H;
	UBRR0L = BAUD_RATE_L;
}

void UART0_display_menu(void)
{
	UART0_transmit_string(menu_description);
}

void UART0_transmit(char data)
{
	while((UCSR0A & (1 << UDRE0)) == 0x00);
	UDR0 = data;
}

void UART0_transmit_string(const char* ch)
{
	uint8_t ch_index;
	for(ch_index = 0; ch[ch_index]; ch_index++)
	{
		UART0_transmit(ch[ch_index]);
	}
}

void UART0_transmit_voltage(int volt)
{
	int buf;
	buf = volt % 10;
	UART0_transmit(volt / 100 + NUMBER_OFFSET);
	UART0_transmit('.');
	UART0_transmit(buf / 10 + NUMBER_OFFSET);
	UART0_transmit(buf % 10 + NUMBER_OFFSET);
	UART0_transmit('V');
	UART0_transmit('\r');
}

void UART0_clear(void)
{
	UCSR0B = 0x00;
	UCSR0C = 0x00;
	UBRR0H = 0;
	UBRR0L = 0;
}