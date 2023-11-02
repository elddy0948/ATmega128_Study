/*
 * DIYBoardTest.c
 *
 * Created: 2023-11-02 오후 9:19:49
 * Author : HJ KIM
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;			// B 레지스터를 출력용으로 설정
	
    while (1) 
    {
		PORTB = 0x00;		// 0000 0000
		_delay_ms(1000);
		
		PORTB = 0xFF;		// 1111 1111
		_delay_ms(1000);
    }
	
	return 0;
}

