/*
 * uart.h
 *
 * Created: 2021-04-20 오전 10:48:32
 *  Author: User
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>

char tran_q[100], reci_q[100];
int tran_q_pos, tran_q_cur, reci_q_pos, reci_q_cur;

void uart_init();

void uart_write(unsigned char data);
unsigned char uart_read_available();
unsigned char uart_read();

#endif /* UART_H_ */