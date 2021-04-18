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
    int i, j;
	DDRB = 0xff;
	
	twi_init();
	lcd_init();

    while (1) 
    {
		for(i = 0; i < 3; i++)
		{
			lcd_send_cmd(0x80 | 0x50);
			for(j = 0; j < 16; j++)
			{
				lcd_send_data(i * 0x20 + j + 0x20);
			}
			_delay_ms(2000);
		}
    }
}