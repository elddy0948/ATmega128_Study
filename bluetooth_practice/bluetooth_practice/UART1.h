/*
 * UART1.h
 *
 * Created: 2024-05-01 오후 10:12:26
 *  Author: HoJoon
 */ 


#ifndef UART1_H_
#define UART1_H_

void UART1_init(void);
void UART1_transmit(char data);
unsigned char UART1_receive(void);
void UART1_print_string(char* str);
void UART1_print_1_byte_number(uint8_t n);

#endif /* UART1_H_ */