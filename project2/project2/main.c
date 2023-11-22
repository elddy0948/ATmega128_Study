/*
 * project2.c
 *
 * Created: 2023-11-20 오후 2:38:11
 * Author : HJ KIM
 */ 

#include "seven_segments.h"
#include "interrupt_main.h"
#include "timer_main.h"
#include "adc_main.h"
#include "uart0_main.h"

uint8_t bday_flag = 1;
uint8_t display_count = 0;
int val = 0;
char* uart_message = "";
uint8_t timer0_usage = 0;
uint8_t n1000, n100, n10, n1;
uint8_t menu_status = MENU_ENABLE;
uint8_t menu_input = 0;

int main(void)
{
	DDRC = 0xFF;
	PORTC = 0xFF;
	
	SEG_init();
	UART0_init();
	SEG_display_birthday();
	
	sei();
		
    while (1) 
    {
		if(menu_status == MENU_ENABLE)
		{
			menu_status = MENU_DISABLE;
			UART0_display_menu();
		}

		if(EINT4_FLAG_BIT == 1)
		{
			EINT4_FLAG_BIT = 0;
			display_count = 0;
			ADC_clear();
			TIMER_clear_all();
			TIMER2_ovf_init();
			timer0_usage = TIMER0_FOR_ADC;
			TIMER0_ovf_init(500);
		}
		if(EINT5_FLAG_BIT == 1)
		{
			EINT5_FLAG_BIT= 0;
			display_count = 0;
			bday_flag = 1;
			ADC_clear();
			TIMER_clear_all();
			TIMER1_compa_init();
			ADC_init(VCC_FLAG, 0x06, (1 << ADFR));
		}
		if(EINT6_FLAG_BIT == 1)
		{
			EINT6_FLAG_BIT = 0;
			display_count = 0;
			bday_flag = 1;
			ADC_clear();
			TIMER_clear_all();
			TIMER3_pwm_init();
			UART0_transmit_string("FAST PWM START\r");
			timer0_usage = TIMER0_FOR_TIMER3;
			TIMER0_ovf_init(3500);	// 7SEC
			uart_message = "FAST PWM STOPPED\r";
		}
		if(EINT7_FLAG_BIT == 1)
		{
			EINT7_FLAG_BIT = 0;
			display_count = 0;
			bday_flag = 1;
			ADC_clear();
			TIMER_clear_all();
			TIMER3_pc_pwm_init();
			UART0_transmit_string("PC PWM START\r");
			timer0_usage = TIMER0_FOR_TIMER3;
			TIMER0_ovf_init(4000);	// 8SEC
			uart_message = "PC PWM STOPPED\r";
		}
		if(TIMER0_OVF_FLAG_BIT == 1)
		{
			TIMER0_OVF_FLAG_BIT = 0;
			if(timer0_usage == TIMER0_FOR_ADC)
			{
				timer0_usage = 0;
			}
			else if(timer0_usage == TIMER0_FOR_TIMER3)
			{
				timer0_usage = 0;
				TIMER_clear_all();
				UART0_transmit_string(uart_message);
				menu_status = MENU_ENABLE;
			}
		}
		if(TIMER2_OVF_FLAG_BIT == 1)
		{
			TIMER2_OVF_FLAG_BIT = 0;
			ADC_init(TEMP_FLAG, 0x07, 0x00);
		}
		if(TIMER1_COMPA_FLAG_BIT == 1)
		{
			TIMER1_COMPA_FLAG_BIT = 0;
			display_count++;
			val = ADC_get_value(100.0);
			UART0_transmit_voltage(val);
			
			if(display_count == 10) {
				TIMER_clear_all();
				ADC_clear();
				menu_status =MENU_ENABLE;
			}
		}
		if(adc_flag == ADC_TEMP_COMPLETE_FLAG)
		{
			adc_flag = ADC_CLEAR_FLAG;
			bday_flag = 0;
			display_count++;
			
			val = ADC_get_value(1000.0);
			n1000 = val / 1000;
			n100 = (val % 1000) / 100;
			n10 = ((val % 1000) % 100) / 10;
			n1 = ((val % 1000) % 100) % 10;
			
			if(display_count == 10)
			{
				bday_flag = 1;
				TIMER_clear_all();
				ADC_clear();
			}
		}
		if(adc_flag == ADC_VCC_COMPLETE_FLAG)
		{
			adc_flag = ADC_CLEAR_FLAG;
		}
		if(EINT4_ENABLE_FLAG_BIT == 1)
		{
			EINT4_ENABLE_FLAG_BIT = 0;
			EINT4_init();
			UART0_transmit_string("ENABLE EINT4...\r");
			menu_status = MENU_ENABLE;
		}
		if(EINT5_ENABLE_FLAG_BIT == 1)
		{
			EINT5_ENABLE_FLAG_BIT = 0;
			EINT5_init();
			UART0_transmit_string("ENABLE EINT5...\r");
		}
		if(EINT6_ENABLE_FLAG_BIT == 1)
		{
			EINT6_ENABLE_FLAG_BIT = 0;
			EINT6_init();
			UART0_transmit_string("ENABLE EINT6...\r");
		}
		if(EINT7_ENABLE_FLAG_BIT == 1)
		{
			EINT7_ENABLE_FLAG_BIT = 0;
			EINT7_init();
			UART0_transmit_string("ENABLE EINT7... \r");
		}
		if (bday_flag)
		{
			SEG_display_4byte(digits_display);
		}
		else
		{
 			if(timer0_count % 4 == 0)
 			{
 				SEG_display_digit(4, n1000);
 			}
 			else if(timer0_count % 4 == 1)
 			{
 				SEG_display_digit(3, n100);
 			}
 			else if(timer0_count % 4 == 2)
 			{
 				SEG_display_digit(2, n10);
				PORTB = PORTB | 0x80;
 			}
 			else if(timer0_count % 4 == 3)
 			{
 				SEG_display_digit(1, n1);
 			}
		}
    }
}