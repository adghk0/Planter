/*
 * Planter_2021.c
 *
 * Created: 2021-04-18 오후 4:52:50
 * Author : rudwn
 */

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

//i2c
#include "files/twi.h"
#include "files/lcd_twi.h"


int main(void)
{
	DDRB = 0xff;
	
	twi_init();
	lcd_init();

	lcd_send_string("hello world!");
	lcd_move(0, 1);
	lcd_send_string("Lee woo sub ba boo");
	while (1) 
    {
    }
}