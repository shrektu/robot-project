
#include "lcd.h"

#include <stdarg.h>
#include <stdio.h>

#include <util/delay.h>

/* Static helper functions */


static void lcd_out_nibble(uint8_t nibbleToWrite)
{

    if(nibbleToWrite & 0x01)
        LCD_DB4_PORT |= LCD_DB4;
    else
        LCD_DB4_PORT  &= ~LCD_DB4;

    if(nibbleToWrite & 0x02)
        LCD_DB5_PORT |= LCD_DB5;
    else
        LCD_DB5_PORT  &= ~LCD_DB5;

    if(nibbleToWrite & 0x04)
        LCD_DB6_PORT |= LCD_DB6;
    else
        LCD_DB6_PORT  &= ~LCD_DB6;

    if(nibbleToWrite & 0x08)
        LCD_DB7_PORT |= LCD_DB7;
    else
        LCD_DB7_PORT  &= ~LCD_DB7;
}


static uint8_t lcd_in_nibble(void)
{
    uint8_t tmp = 0;

    if(LCD_DB4_PIN & LCD_DB4)
        tmp |= (1 << 0);
    if(LCD_DB5_PIN & LCD_DB5)
        tmp |= (1 << 1);
    if(LCD_DB6_PIN & LCD_DB6)
        tmp |= (1 << 2);
    if(LCD_DB7_PIN & LCD_DB7)
        tmp |= (1 << 3);
    return tmp;
}


static void lcd_write(uint8_t dataToWrite)
{
    LCD_DB4_DIR |= LCD_DB4;
    LCD_DB5_DIR |= LCD_DB5;
    LCD_DB6_DIR |= LCD_DB6;
    LCD_DB7_DIR |= LCD_DB7;

    LCD_RW_PORT &= ~LCD_RW;
    LCD_E_PORT |= LCD_E;
    lcd_out_nibble(dataToWrite >> 4);
    LCD_E_PORT &= ~LCD_E;
    LCD_E_PORT |= LCD_E;
    lcd_out_nibble(dataToWrite);
    LCD_E_PORT &= ~LCD_E;
    while(lcd_read_status()&0x80);
}


static uint8_t lcd_read(void)
{
    uint8_t tmp = 0;
    LCD_DB4_DIR &= ~LCD_DB4;
    LCD_DB5_DIR &= ~LCD_DB5;
    LCD_DB6_DIR &= ~LCD_DB6;
    LCD_DB7_DIR &= ~LCD_DB7;

    LCD_RW_PORT |= LCD_RW;
    LCD_E_PORT |= LCD_E;
    tmp |= (lcd_in_nibble() << 4);
    LCD_E_PORT &= ~LCD_E;
    LCD_E_PORT |= LCD_E;
    tmp |= lcd_in_nibble();
    LCD_E_PORT &= ~LCD_E;
    return tmp;
}



/* Function definitions */

void lcd_write_command(uint8_t commandToWrite)
{
    LCD_RS_PORT &= ~LCD_RS;
    lcd_write(commandToWrite);
}


uint8_t lcd_read_status(void)
{
    LCD_RS_PORT &= ~LCD_RS;
    return lcd_read();
}


void lcd_write_data(uint8_t dataToWrite)
{
    LCD_RS_PORT |= LCD_RS;
    lcd_write(dataToWrite);
}


uint8_t lcd_read_data(void)
{
    LCD_RS_PORT |= LCD_RS;
    return lcd_read();
}


void lcd_print_text(char * text)
{
    while (*text)
    lcd_write_data(*text++);
}


void lcd_go_to(uint8_t x, uint8_t y)
{
    lcd_write_command(HD44780_DDRAM_SET | (x + (0x40 * y)));
}


void lcd_clear(void)
{
    lcd_write_command(HD44780_CLEAR);
    _delay_ms(2);
}


void lcd_home(void)
{
    lcd_write_command(HD44780_HOME);
    _delay_ms(2);
}


void lcd_init(void)
{
    uint8_t i;
    LCD_DB4_DIR |= LCD_DB4; 
    LCD_DB5_DIR |= LCD_DB5; 
    LCD_DB6_DIR |= LCD_DB6; 
    LCD_DB7_DIR |= LCD_DB7; 
    LCD_E_DIR 	|= LCD_E;   
    LCD_RS_DIR 	|= LCD_RS;  
    LCD_RW_DIR 	|= LCD_RW;  
    _delay_ms(15); 
    LCD_RS_PORT &= ~LCD_RS; 
    LCD_E_PORT &= ~LCD_E;  
    LCD_RW_PORT &= ~LCD_RW;

    for (i = 0; i < 3; i++) 
    {
        LCD_E_PORT |= LCD_E;
        lcd_out_nibble(0x03);
        LCD_E_PORT &= ~LCD_E;
        _delay_ms(5);
    }

    LCD_E_PORT |= LCD_E;
    lcd_out_nibble(0x02);
    LCD_E_PORT &= ~LCD_E;

    _delay_ms(1); 
    lcd_write_command(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT);
    lcd_write_command(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF);
    lcd_write_command(HD44780_CLEAR);
    lcd_write_command(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);
    lcd_write_command(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
}


void lcd_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    
    char buffer[17];    // 16 chars for LCD 2x16 + 1 for end of string '\0'
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    
    lcd_print_text(buffer);

    va_end(args);
}
