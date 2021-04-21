/*
 * uart.c
 *
 * Created: 2021-04-20 오전 10:48:22
 *  Author: User
 */ 

#include "uart.h"

#include "lcd_twi.h"

void uart_init()
{
	tran_q_pos = 0; tran_q_cur = 0;
	reci_q_pos = 0; reci_q_cur = 0;
	
	// Baud Rate = 115200
	UBRR0H = 0;
	UBRR0L = 8;
	
	UCSR0A = 0x00;
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXCIE0) | (1<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (3<<UCSZ00);
	
	sei();
}

ISR(USART_UDRE_vect)

void uart_write(unsigned char data)
{
	/* DEBUG */
	lcd_send_data(data);
	
	tran_q[tran_q_cur++] = data;
}
unsigned char uart_read()
{
	
}
