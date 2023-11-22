
/*
 * timer_main.c
 *
 * Created: 2023-11-20 오후 3:22:06
 *  Author: HJ KIM
 */ 

#include "timer_main.h"

int timer0_count = 0;
int timer1_count = 0;
int timer2_count = 0;

uint16_t BASE_COUNT = 0;
uint8_t TIMER2_OVF_FLAG_BIT = 0;
uint8_t TIMER1_COMPA_FLAG_BIT = 0;
uint8_t TIMER0_OVF_FLAG_BIT = 0;

/* TIMER SERVICE ROUTINE */
ISR(TIMER0_OVF_vect)
{
	cli();
	timer0_count++;
	if(timer0_count >= BASE_COUNT)
	{
		TIMER0_OVF_FLAG_BIT = 1;
		timer0_count = 0;
	}
	TCNT0 = TCNT0_BASE;

	sei();
}

ISR(TIMER2_OVF_vect)
{
	cli();
	
	timer2_count++;
	if(timer2_count >= 200)
	{
		TIMER2_OVF_FLAG_BIT = 1;
		timer2_count = 0;
	}
	TCNT2 = TCNT2_BASE;
	
	sei();
}

ISR(TIMER1_COMPA_vect)
{
	cli();
	timer1_count++;
	if(timer1_count >= 10)
	{
		TIMER1_COMPA_FLAG_BIT = 1;
		timer1_count = 0;
	}
	TCNT1 = 0;
	sei();
}

/* TIMER INIT */
void TIMER0_ovf_init(uint16_t cnt)
{
	timer0_count = 0;
	
	BASE_COUNT = cnt;
	TIMSK |= (1 << TOIE0);
	TCNT0 = TCNT0_BASE;
	TCCR0 |= (1 << CS02) | (1 << CS01);
}

void TIMER1_compa_init(void)
{
	timer1_count = 0;
	TIMSK |= (1 << OCIE1A);
	TCCR1B |= (1 << WGM12);
	OCR1AH = OCR1_H;
	OCR1AL = OCR1_L;
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

void TIMER2_ovf_init(void)
{
	timer2_count = 0;
	TIMSK |= (1 << TOIE2);
	TCNT2 = TCNT2_BASE;
	TCCR2 |= (1 << CS22) | (1 << CS20); // 1024
}

void TIMER3_pwm_init(void)
{
	DDRE |= (1 << PORTE3);

	TCCR3A |= (1 << COM3A1) | (1 << COM3A0);
	TCCR3A |= (1 << WGM31);	// MODE 6: FAST PWM
	TCCR3B |= (1 << WGM32);
	OCR3AH = OCR3_H;
	OCR3AL = OCR3_L;
	
	TCCR3B |= (1 << CS31) | (1 << CS30);
}

void TIMER3_pc_pwm_init(void)
{
	DDRE |= (1 << PORTE3);	
	TCCR3A |= (1 << COM3A1) | (1 << COM3A0);
	TCCR3A |= (1 << WGM31);	// MODE 2: PC PWM
	OCR3AH = OCR3_H;
	OCR3AL = OCR3_L;
	
	TCCR3B |= (1 << CS31) | (1 << CS30);
}

/* CLEAR TIMERS */
void TIMER_clear_all(void)
{
	TIMER0_clear();
	TIMER1_clear();
	TIMER2_clear();
	TIMER3_clear();
}

void TIMER0_clear(void)
{
	TIMSK &= ~(1 << TOIE0);
	TCCR0 = 0x00;
}

void TIMER1_clear(void)
{
	TIMSK &= ~(1 << OCIE1A);
	TCCR1B = 0x00;
	OCR1A = 0;
}

void TIMER2_clear(void)
{
	TCCR2 = 0x00;
	TIMSK &= ~(1 << TOIE2);
	TCNT2 = 0;
}

void TIMER3_clear(void)
{
	DDRE = 0x00;
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}