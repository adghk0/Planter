/*
 * lcd_twi.c
 *
 * Created: 2021-04-18 오후 9:26:41
 *  Author: rudwn
 */ 

#include "lcd_twi.h"

void lcd_send_cmd_4bit(unsigned char cmd_half)
{
	twi_send_byte(LCD_ADDR, cmd_half | (1<<LCD_EN) | (lcd_backlight << LCD_BL));
	_delay_ms(2);
	twi_send_byte(LCD_ADDR, cmd_half | (lcd_backlight << LCD_BL));
	_delay_ms(2);
}
void lcd_send_cmd(unsigned char cmd)
{
	lcd_send_cmd_4bit(cmd & 0xf0);
	lcd_send_cmd_4bit((cmd << 4) & 0xf0);
}
void lcd_send_data_4bit(unsigned char data_half)
{
	twi_send_byte(LCD_ADDR, data_half | (1<<LCD_EN) | (1<<LCD_RS) | (lcd_backlight << LCD_BL));
	_delay_ms(2);
	twi_send_byte(LCD_ADDR, data_half | (1<<LCD_RS) | (lcd_backlight << LCD_BL));
	_delay_ms(2);
}
void lcd_send_data(char data)
{
	lcd_send_data_4bit((data << 4) & 0xf0);
	lcd_send_data_4bit(data & 0xf0);
}

void lcd_init()
{
	twi_init();
	
	// 4bit Power On
	lcd_backlight = 0;
	lcd_send_cmd_4bit(0x30);
	_delay_ms(20);
	lcd_send_cmd_4bit(0x30);
	_delay_ms(10);
	lcd_send_cmd_4bit(0x30);
	_delay_us(200);
	lcd_send_cmd_4bit(0x20);
	_delay_ms(10);
	
	// 4bit Initialize
	lcd_send_cmd(0x28); // Function set
	lcd_send_cmd(0x01); // Clear
	lcd_send_cmd(0x06); // Entry set
	lcd_backlight = 1;
	lcd_send_cmd(0x0c); // Display
	
	
}