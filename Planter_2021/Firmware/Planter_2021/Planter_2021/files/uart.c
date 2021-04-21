/*
 * uart.c
 *
 * Created: 2021-04-21 ¿ÀÈÄ 1:45:57
 *  Author: rudwn
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

#define F_CPU 16000000L
#define RX_BUFFER_SIZE 128
#define TX_BUFFER_SIZE 256

static volatile uint8_t txBuffer[TX_BUFFER_SIZE];
static volatile uint8_t txBufferIdx;
static volatile uint8_t txBufferCur;
static volatile uint8_t rxBuffer[RX_BUFFER_SIZE];
static volatile uint8_t rxBufferIdx;
static volatile uint8_t rxBufferCur;

// USART empty UDR interrupt
ISR(USART_UDRE_vect)
{
	uint8_t sreg = SREG;
	cli();

	if (txBufferIdx != txBufferCur)
	{
		UDR0 = txBuffer[txBufferCur];
		txBufferCur++;
	}
	else
	{
		// disable TX interrupt
		UCSR0B = ((1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0));
	}
	
	SREG = sreg;
}
ISR(USART_RX_vect)
{
	uint8_t sreg = SREG;
	cli();

	rxBuffer[rxBufferCur++] = UDR0;
	// if overflow, return to first
	rxBufferIdx &= (RX_BUFFER_SIZE-1);

	SREG = sreg;
}

void uart_init(uint32_t baudrate)
{
	cli();

	UBRR0 = (F_CPU / 4 / baudrate - 1) / 2;
	UCSR0A = (1<<U2X0);
	UCSR0B = ((1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0));
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

	txBufferIdx = txBufferCur = 0;
	rxBufferIdx = rxBufferCur = 0;

	sei();
}

void uart_put_string(const uint8_t *str)
{
	uint8_t sreg = SREG;
	cli();

	while(*str) {
		txBuffer[txBufferIdx++] = *str++;
	}

	UCSR0B = ((1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) | (1<<UDRIE0));

	SREG = sreg;
}
void uart_put_char(const uint8_t c)
{
	uint8_t sreg = SREG;
	cli();

	txBuffer[txBufferIdx++] = c;

	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) | (1<<UDRIE0);

	SREG = sreg;
}

uint8_t uart_get_char(void)
{
	if (rxBufferIdx == rxBufferCur) return 0;

	uint8_t c;
	uint8_t sreg=SREG;
	cli();

	c = rxBuffer[rxBufferIdx++];

	rxBufferIdx &= (RX_BUFFER_SIZE-1);

	SREG=sreg;

	return c;
}
uint8_t uart_available(void)
{
	uint8_t sreg = SREG;
	cli();
	
	uint8_t cur = rxBufferCur;
	uint8_t idx = rxBufferIdx;
	uint8_t r = 0;

	if (idx - cur) {
		cur += RX_BUFFER_SIZE;
		r = (cur - idx);
	} else {
		r = (cur - idx);
	}

	SREG = sreg;

	return r;
}
void uart_rx_flush(void)
{
	rxBufferIdx = rxBufferCur = 0;
}
