/*
 * Timer_Counter_8bits.c
 *
 * Created: 2023-11-13 오후 9:55:22
 * Author : HJ KIM
 */ 
#include "comp_int.h"

int main(void)
{
	DDRB |= 0x01;
	PORTB = 0x00;
	
	INIT_TCINT();
	
    while (1) 
    {
		comp_int_main();
    }
}

