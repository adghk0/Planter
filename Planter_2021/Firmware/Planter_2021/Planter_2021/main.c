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
#include "files/uart.h"

void test(char *cmd)
{
	char read = 0;
	lcd_move(0, 0);
	lcd_send_string("SEND-");
	lcd_send_string(cmd);
	
	uart_put_string(cmd);
	
	
	_delay_ms(100);
	while(uart_available())
	{
		read = uart_get_char();
		lcd_move(0, 1);
		lcd_send_data(read);
		lcd_send_data(read / 100 + '0');
		lcd_send_data(read / 10 % 10 + '0');
		lcd_send_data(read % 10 + '0');
		lcd_send_data(' ');
		_delay_ms(1000);
	}
	lcd_send_string("    ");
}

int main(void)
{
	int i = 0;
	char read;
	twi_init();
	lcd_init();
	uart_init(115200);
	
	_delay_ms(3000);
	
	while (1) 
    {
		test("AT\r\n");
		_delay_ms(5000);
		
    }
}
/*

int main(void)
{
	char read;
	char form[20];
	
	twi_init();
	lcd_init();
	uart_init();
	
	uart_write('A');
	uart_write('T');
	uart_write('\r');
	uart_write('\n');
	lcd_move(0, 0);
	lcd_send_string("SEND AT");
	
	lcd_move(0, 1);
	while (1) 
    {
		read = uart_read();
		form[0] = read >> 4 + '0';
		form[1] = read & 0x0f + '0';
		form[2] = ' ';
		form[3] = '\0';
		lcd_send_string(form);
    }
}
*/