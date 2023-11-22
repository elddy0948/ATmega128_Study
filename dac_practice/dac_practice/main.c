/*
 * dac_practice.c
 *
 * Created: 2023-11-22 오후 2:31:53
 * Author : HJ KIM
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define CLK_HIGH (PORTD |= (1 << PORTD0));
#define CLK_LOW (PORTD &= ~(1 << PORTD0));
#define LD_HIGH (PORTD |= (1 << PORTD2));
#define LD_LOW (PORTD &= ~(1 << PORTD2));
#define DATA_HIGH (PORTD |= (1 << PORTD1));
#define DATA_LOW (PORTD &= ~(1 << PORTD1));
#define DATA_SIZE 19
#define TCNT0_BASE 236

const uint16_t DAC_TABLE[] = {
	0x000, 0x01A, 0x034, 0x04D, 0x067, 0x080, 0x09A, 0x0C0, 0x0E7, 0x100,
	0x0E7, 0x0C0, 0x09A, 0x080, 0x067, 0x04D, 0x034, 0x01A, 0x000
};

uint8_t TIMER0_FOR_CLK = 0;
uint8_t EINT4_FLAG_BIT = 0;
uint8_t clk_timer_counter = 0;
uint8_t clk_status = 0;

// 10us
ISR(TIMER0_OVF_vect)
{
	cli();
	clk_timer_counter++;
	if(clk_timer_counter >= 6) {
		clk_timer_counter = 0;
		TIMER0_FOR_CLK = 1;
	}
	
	sei();
}

ISR(INT4_vect)
{
	cli();
	EINT4_FLAG_BIT = 1;
	sei();
}

void TIMER0_init(void)
{
	TIMSK |= (1 << TOIE0);
	TCNT0 = TCNT0_BASE;
	TCCR0 |= (1 << CS01);
}

void TIMER0_clear(void)
{
	TCCR0 &= ~(1 << CS01);
}

void EINT4_init(void)
{
	EIMSK |= (1 << INT4);
	EICRB |= (1 << ISC41);
}

int main(void)
{
	uint8_t table_index = 0;
	uint8_t data_index = 0;
	uint8_t data_status = 0;
	
	DDRD |= 0x07;	// PORTD0, PORTD1, PORTD2
	LD_LOW;
	
	EINT4_init();
	
	sei();
	
    while (1) 
    {
		if(EINT4_FLAG_BIT == 1)
		{
			EINT4_FLAG_BIT = 0;
			table_index++;
			data_index = 0;
			TIMER0_init();
		}
		
		if(TIMER0_FOR_CLK == 1)
		{
			TIMER0_FOR_CLK = 0;
			if(clk_status == 1)
			{
				CLK_LOW;
				clk_status = 0;
				if(data_index == 10)
				{
					// END OF ONE 10 bit
					data_status = 1;
					DATA_LOW;
				}
				else
				{
					// DATA SET
					if(((DAC_TABLE[table_index] << data_index) & 0x200) == 0x200)
					{
						DATA_HIGH;
					}
					else
					{
						DATA_LOW;
					}
					
					data_index++;
				}
			}
			else if(clk_status == 0)
			{
				CLK_HIGH;
				clk_status = 1;
			}
		}
		
		if(data_status == 1)
		{
			data_status = 0;
			TIMER0_clear();
			_delay_us(50);
			LD_HIGH;
			_delay_us(50);
			LD_LOW;
			_delay_us(50);
		}
    }
}

