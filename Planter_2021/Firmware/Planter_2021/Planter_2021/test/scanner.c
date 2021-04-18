/*
 * scanner.c
 *
 * Created: 2021-04-19 오전 12:32:24
 *  Author: rudwn
 */ 

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
	unsigned char i = 0, re;
    DDRB = 0xff;
	
	twi_init();
	//lcd_init();
	
	
    while (1) 
    {
		for(i = 0; i < 128; i++)
		{
			re = twi_send_byte(i, i);
			_delay_ms(1);
			PORTB = re;
			if(re == 0x00)
			{
				PORTB = 0xff;
				_delay_ms(500);
				PORTB = 0x00;
				_delay_ms(500);
				PORTB = i & 0x0f;
				_delay_ms(1000);
				PORTB = i >> 4;
				_delay_ms(1000);
			}
		}
    }
}

