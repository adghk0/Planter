/*
 * twi.h
 *
 * Created: 2021-04-18 오후 6:30:57
 *  Author: rudwn
 */ 
// TWBR – TWI Bit Rate Register
// TWCR – TWI Control Register
// TWSR – TWI Status Register
// TWDR – TWI Data Register
// TWAR – TWI (Slave) Address Register
// TWAMR – TWI (Slave) Address Mask Register

#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

#define TWI_DDR		DDRC
#define TWI_MSK		0x30

// TWCR
/*
#define TWI_TWINT	0x80	// TWINT: TWI Interrupt Flag
#define TWI_TWEA	0x40	// TWEA: TWI Enable Acknowledge Bit
#define TWI_TWSTA	0x20	// TWSTA: TWI START Condition B
#define TWI_TWSTO	0x10	// TWSTO: TWI STOP Condition Bit
#define TWI_TWWC	0x08	// TWWC: TWI Write Collision Flag
#define TWI_TWEN	0x04	// TWEN: TWI Enable Bit
#define TWI_TWIE	0x01	// TWIE: TWI Interrupt Enable
*/

// TWSR
#define TWI_STATUS	0xf8
#define TWI_START	0x08
#define TWI_REPEAT	0x10
#define TWI_W_ACK	0x18
#define	TWI_W_NACK	0x20
#define TWI_WD_ACK	0x28
#define TWI_WD_NACK	0x30
#define TWI_LOST	0x38
#define TWI_R_ACK	0x40
#define TWI_R_NACK	0x48
#define TWI_RD_ACK	0x50
#define TWI_RD_NACK	0x58


// TWI
void twi_init();

// Master Mode
unsigned char twi_send_byte(unsigned char addr, unsigned char data);

// Master Transmitter Mode


#endif /* TWI_H_ */