
/*
 * thermistor_example.c
 *
 * Created: 2023-11-20 오전 11:23:49
 *  Author: HJ KIM
 */

#include "thermistor_example.h"

const unsigned char seg_pat[10]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
int ad_val;
int count = 0;

ISR(TIMER0_OVF_vect)
{
	cli();
	count++;
	if (count == 100)
	{
		count = 0;
		adc_main();
	}
	TCNT0 = 100;
	sei();
}

void init_ports(void)
{
	DDRC = 0xFF;
	DDRB = 0xF0;
	DDRD = 0xF0;
	DDRG = 0x0F;
	PORTC = 0xFF;
}

void init_timer(void)
{
	TIMSK |= (1 << TOIE0);
	TCCR0 |= (1 << CS00);
	TCCR0 |= (1 << CS01);
	TCCR0 |= (1 << CS02);
	TCNT0 = 100;
}

void init_adc(void)
{
	ADMUX = 0x07;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= 0x07;
}

void display_adc(int val)
{
	float fval;
	int ival, buf;
	unsigned char N100, N10, N1;
	fval = (float)val * 5.0 / 1023.0; // 전압 값으로 변환
	ival = (int)(fval * 1000.0 + 0.5); // 반올림 후 정수화, (소수 둘째자리까지)
	N100 = ival / 100; // 정수부 추출
	buf = ival % 100;
	N10 = buf / 10; // 소수 첫째 자리 추출
	N1 = buf % 10; // 소수 둘째 자리 추출
	PORTG = 0b00001000; // PG3=1, 소수 둘째 자리
	PORTD = ((seg_pat[N1] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[N1] & 0x70 ) | (PORTB & 0x0F);
	_delay_ms(1);
	PORTG = 0b00000100; // PG2=1, 소수 첫째 자리
	PORTD = ((seg_pat[N10] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[N10] & 0x70 ) | (PORTB & 0x0F);
	PORTB = PORTB | 0x80; // DP on(소수점)
	_delay_ms(1);
	PORTG = 0b00000010; // PG1=1, 정수부
	PORTD = ((seg_pat[N100] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[N100] & 0x70 ) | (PORTB & 0x0F);
	
	_delay_ms(1);
}

void adc_main(void)
{
	ADCSRA = 0xC7;
	while((ADCSRA & 0x10) == 0);
	ad_val = (int)ADCL + ((int)ADCH << 8);
}
