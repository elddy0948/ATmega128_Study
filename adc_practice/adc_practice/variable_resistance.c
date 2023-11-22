
/*
 * variable_resistance.c
 *
 * Created: 2023-11-20 오전 10:30:38
 *  Author: HJ KIM
 */ 

#include "variable_resistance.h"

unsigned char seg_pat[10]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void init_ports(void)
{
	DDRB |= 0xF0;
	DDRD |= 0xF0;
	DDRG |= 0x0F;
}

void init_adc(void)
{
	ADMUX = 0x06;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= 0x07;
}

void ad_disp(int val)
{
	float fval;
	int ival, buf;
	unsigned char N100, N10, N1;
	fval = (float)val * 5.0 / 1024.0; // 전압 값으로 변환
	ival = (int)(fval * 100.0 + 0.5); // 반올림 후 정수화, (소수 둘째자리까지)
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
	_delay_ms(1);
	PORTG = 0b00000010; // PG1=1, 정수부
	PORTD = ((seg_pat[N100] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[N100] & 0x70 ) | (PORTB & 0x0F);
	PORTB = PORTB | 0x80; // DP on(소수점)
	_delay_ms(1);
}

void adc_main()
{
	int ad_val;
	ADCSRA = 0xC7;
	while((ADCSRA & 0x10) == 0);
	ad_val = (int)ADCL + ((int)ADCH << 8);
	ad_disp(ad_val);
}