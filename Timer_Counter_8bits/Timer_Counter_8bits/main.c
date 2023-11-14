/*
 * Timer_Counter_8bits.c
 *
 * Created: 2023-11-13 오후 9:55:22
 * Author : HJ KIM
 */ 
#include "overflow_int.h"

int main(void)
{
	DDRC |= 0x01;
	PORTC = 0xFF;
	
	INIT_OF_TCINT();
	
    while (1) 
    {
    }
}

