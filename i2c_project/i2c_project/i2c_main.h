
/*
 * i2c_main.h
 *
 * Created: 2023-11-06 오후 6:07:04
 *  Author: HJ KIM
 */ 
#pragma once
#ifndef _I2C_MAIN_H
#define _I2C_MAIN_H

#include <avr/io.h>

#define CLK_OUT DDRD |= 0x01

#define CLK_HIGH PORTD |= 0x01
#define CLK_LOW PORTD &= 0xFE

#define DATA_OUT DDRD |= 0x02
#define DATA_IN DDRD &= 0xFD

#define DATA_HIGH PORTD |= 0x02
#define DATA_LOW PORTD &= 0xFD

#define BASE_DEVICE_ADDRESS 0xA0

#define ACK 0x00
#define NOACK 0x02
#define PAGE_MAX 16

#define GET_BIT(bits, i) ((bits << i) & 0x80)

typedef unsigned char uint8_t;

void i2c_start();
void i2c_stop();

void write_data(uint8_t data);
uint8_t receive_response();

uint8_t read_data();
void send_response(uint8_t data);

void i2c_device_address_setup(uint8_t device_address);
void i2c_address_setup(uint8_t address);

void i2c_byte_write(uint8_t data);
void i2c_page_write(uint8_t page[], uint8_t page_size);

void i2c_byte_read();
void i2c_page_read(uint8_t page_size);

#endif /*_I2C_MAIN_H */