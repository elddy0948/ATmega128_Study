
/*
 * free_running.c
 *
 * Created: 2023-11-20 오전 10:46:39
 *  Author: HJ KIM
 */ 
#include "free_running.h"

const unsigned char seg_pat[10]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void init_ports(void)
{
	DDRB = 0xF0;
	DDRD = 0xF0;
	DDRG = 0x0F;
}

void init_adc(void)
{
	ADMUX = 0x06;
	ADCSRA = 0xE7;
}

void ad_disp(int pos, int val)
{
	PORTG |= 0x00;
	PORTG |= (1 << (4 - pos));
	PORTD = ((seg_pat[val] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[val] & 0x70 ) | (PORTB & 0x0F);
	_delay_ms(1);
}

void adc_main(void)
{
	int ad_val;
	ad_val = (int)ADCL + ((int)ADCH << 8);
	
	float fval;
	int ival, buf;
	
	fval = (float)ad_val * 5.0 / 1023.0;
	ival = (int)(fval * 100.0 + 0.5);
	ad_disp(3, ival / 100);
	buf = ival % 100;
	
	ad_disp(2, buf / 10);
	ad_disp(1, buf % 10);
}