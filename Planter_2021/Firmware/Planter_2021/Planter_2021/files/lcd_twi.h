/*
 * lcd_twi.h
 *
 * Created: 2021-04-18 오후 9:26:31
 *  Author: rudwn
 */ 


#ifndef LCD_TWI_H_
#define LCD_TWI_H_

// LCD Address
#define LCD_ADDR	0x27

// TWI GP Set
#define LCD_RS	0
#define LCD_RW	1
#define LCD_EN	2
#define LCD_BL	3
#define LCD_D4	4
#define LCD_D5	5
#define LCD_D6	6
#define LCD_D7	7

#include <util/delay.h>
#include "twi.h"

unsigned char lcd_backlight;

void lcd_send_cmd(unsigned char cmd);
void lcd_send_data(char data);

void lcd_init();

#endif /* LCD_TWI_H_ */