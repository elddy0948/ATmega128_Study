/*
 * interrupt_study.c
 *
 * Created: 2023-11-13 오후 9:10:39
 * Author : HJ KIM
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

// tell compiler that this `value` can change outside `main` function
volatile int value = 0;

ISR(INT0_vect)
{
	value = (value + 1) % 2;	
}

int main(void)
{
	int local_value;
	
    while (1) 
    {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			local_value = value;
		}
		
		if (local_value == 1) 
		{
			// DO SOMETHING ...
		}
    }
	
	return 0;
}

