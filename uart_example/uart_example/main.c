/*
 * uart_example.c
 *
 * Created: 2023-11-16 오후 10:37:40
 * Author : HJ KIM
 */ 

#include "rxtx_example.h"

int main(void)
{
	init_ports();
	//init_uart1();
	init_eint();

	sei();
	
    while (1) 
    {
		menu_main();
    }
}

