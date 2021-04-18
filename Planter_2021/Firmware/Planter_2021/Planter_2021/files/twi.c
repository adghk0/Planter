/*
 * twi.c
 *
 * Created: 2021-04-18 오후 6:31:06
 *  Author: rudwn
 */ 

#define F_CPU 16000000L

#include "twi.h"

void _twi_wait()
{
	while(!(TWCR & (1<<TWINT)));
}

void twi_init()
{
	TWI_DDR &= ~TWI_MSK;
	// set the Bit Rate
	TWBR = 12;
	TWSR = 0x00;
	TWCR = (1<<TWEN);
}

unsigned char twi_send_byte(unsigned char addr, unsigned char data)
{
	// send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait for SEND
	_twi_wait();
	// check value for ERROR
	if((TWSR & TWI_STATUS) != TWI_START && (TWSR & TWI_STATUS) != TWI_REPEAT)
		return 1;
	
	// load address and write signal
	// ADDR | R=1(W=0)
	TWDR = addr << 1;
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for SEND
	_twi_wait();
	// check value for ERROR
	if((TWSR & TWI_STATUS) != TWI_W_ACK)
		return 2;
	
	// load data
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for SEND
	_twi_wait();
	// check value for ERROR
	if((TWSR & TWI_STATUS) != TWI_WD_ACK)
		return 3;
	
	// send STOP condition
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	return 0x00;
}