
/*
 * rxtx_example.c
 *
 * Created: 2023-11-17 오후 2:06:25
 *  Author: HJ KIM
 */ 
#include "rxtx_example.h"

uint8_t EINT6_FLAG_BIT = 0;
uint8_t RX_COMPLETE_FLAG_BIT = 0;
uint8_t UDRE_FLAG_BIT = 0;
uint8_t data;

const char* menu_str[4] = {
	"MENU DISPLAY\r",
	"1 : LED DISPLAY\r",
	"2 : WRITE WITHOUT YOU\r",
	"Enter number : "
};

const char* pLyrics[10] = {
	"No I can't forget this evening,\r",
	"Or your face as you were leaving.\r",
	"But I guess that's just the way The story goes.\r",
	"You always smile but in your eyes.\r",
	"Your sorrow shows Yes it shows. \r",
	"No I can't forget tomorrow \r",
	"When I think of all my sorrow\r",
	"When I had you there\r",
	"But then I let you go And now it's only fair.\r",
	"That I should let you know What you should know\r",
};

ISR(INT6_vect)
{
	cli();
	EINT6_FLAG_BIT = 1;
	sei();
}

ISR(USART0_RX_vect)
{
	cli();
	RX_COMPLETE_FLAG_BIT = 1;
	data = UDR0;
	sei();
}

void init_ports()
{
	DDRC = 0xFF;
	PORTC = 0xFF;
}

void init_uart1(void)
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0B |= (1 << RXCIE0);
	//UCSR0B |= (1 << UDRIE0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	
	UBRR0H = BAUD_RATE_H;
	UBRR0L = BAUD_RATE_L;
}

void init_eint(void)
{
	EICRB |= (1 << ISC61);
	EIMSK |= (1 << INT6);
}

void menu_main(void)
{
	if (EINT6_FLAG_BIT == 1)
	{
		EINT6_FLAG_BIT = 0;
		init_uart1();
		display_menu();
	}
	if (RX_COMPLETE_FLAG_BIT == 1)
	{
		RX_COMPLETE_FLAG_BIT = 0;
		
		switch(data)
		{
		case '1':
			led_blink();
			break;
		case '2':
			display_withoutyou();
			break;
		default:
			break;
		}
		
		display_menu();
	}
}

void uart1_transmit(char data)
{
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
}

void display_menu(void)
{
	uint8_t i;
	
	for(i = 0; i < 4; ++i)
	{
		display_char(menu_str[i]);	
	}
}

void display_withoutyou(void)
{
	uint8_t i;
	for(i = 0 ; i < 10; ++i)
	{
		display_char(pLyrics[i]);
	}
}

void led_blink(void)
{
	PORTC = 0x00;
	_delay_ms(50);
	PORTC = 0xFF;	
}

void display_char(const char* ch)
{
	uint8_t ch_index;
	for(ch_index = 0; ch[ch_index]; ++ch_index)
	{
		uart1_transmit(ch[ch_index]);
	}
}