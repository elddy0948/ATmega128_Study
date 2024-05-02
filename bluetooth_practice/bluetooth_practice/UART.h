/*
 * UART.h
 *
 * Created: 2024-05-01 오후 10:12:26
 *  Author: HoJoon
 */ 

#ifndef UART_H_
#define UART_H_

void UART0_init(void);
void UART0_transmit(char data);
unsigned char UART0_receive(void);
void UART0_print_string(char* str);

void UART1_init(void);
void UART1_transmit(char data);
unsigned char UART1_receive(void);
void UART1_print_string(char* str);
void UART1_print_1_byte_number(unsigned char n);

#endif /* UART_H_ */