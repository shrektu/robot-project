#pragma once

#ifndef F_CPU
#define F_CPU (16000000U)

#endif

#include <avr/io.h>



/* Macros to connect Arduino UNO pins with LCD pins */

#define LCD_RS_DIR		DDRB
#define LCD_RS_PORT 	PORTB
#define LCD_RS_PIN		PINB
#define LCD_RS			(1 << PINB0)

#define LCD_RW_DIR		DDRB
#define LCD_RW_PORT		PORTB
#define LCD_RW_PIN		PINB
#define LCD_RW			(1 << PINB1)

#define LCD_E_DIR		DDRD
#define LCD_E_PORT		PORTD
#define LCD_E_PIN		PIND
#define LCD_E			(1 << PIND3)

#define LCD_DB4_DIR		DDRB
#define LCD_DB4_PORT	PORTB
#define LCD_DB4_PIN		PINB
#define LCD_DB4			(1 << PINB4)

#define LCD_DB5_DIR		DDRB
#define LCD_DB5_PORT	PORTB
#define LCD_DB5_PIN		PINB
#define LCD_DB5			(1 << PINB5)

#define LCD_DB6_DIR		DDRC
#define LCD_DB6_PORT	PORTC
#define LCD_DB6_PIN		PINC
#define LCD_DB6			(1 << PINC4)

#define LCD_DB7_DIR		DDRC
#define LCD_DB7_PORT	PORTC
#define LCD_DB7_PIN		PINC
#define LCD_DB7			(1 << PINC5)



/* Macros with instructions to HD44780 */

#define HD44780_CLEAR					0x01

#define HD44780_HOME					0x02

#define HD44780_ENTRY_MODE				0x04
	#define HD44780_EM_SHIFT_CURSOR		0
	#define HD44780_EM_SHIFT_DISPLAY	1
	#define HD44780_EM_DECREMENT		0
	#define HD44780_EM_INCREMENT		2

#define HD44780_DISPLAY_ONOFF			0x08
	#define HD44780_DISPLAY_OFF			0
	#define HD44780_DISPLAY_ON			4
	#define HD44780_CURSOR_OFF			0
	#define HD44780_CURSOR_ON			2
	#define HD44780_CURSOR_NOBLINK		0
	#define HD44780_CURSOR_BLINK		1

#define HD44780_DISPLAY_CURSOR_SHIFT	0x10
	#define HD44780_SHIFT_CURSOR		0
	#define HD44780_SHIFT_DISPLAY		8
	#define HD44780_SHIFT_LEFT			0
	#define HD44780_SHIFT_RIGHT			4

#define HD44780_FUNCTION_SET			0x20
	#define HD44780_FONT5x7				0
	#define HD44780_FONT5x10			4
	#define HD44780_ONE_LINE			0
	#define HD44780_TWO_LINE			8
	#define HD44780_4_BIT				0
	#define HD44780_8_BIT				16

#define HD44780_CGRAM_SET				0x40
#define HD44780_DDRAM_SET				0x80



/* Function prototypes for LCD */



/*
 * Function:  lcd_write_command 
 * --------------------
 * Writes a command to HD44780.
 *
 *  uint8_t - HD44780 command to write
 *
 *  returns: void
 */

void lcd_write_command(uint8_t);



/*
 * Function:  lcd_read_status
 * --------------------
 * Returns the HD44780 instruction register
 *
 *  
 *
 *  returns: (uint8_t) instruction register
 */

uint8_t lcd_read_status(void);



/*
 * Function:  lcd_write_data 
 * --------------------
 * Writes a byte of data to HD44780.
 *
 *  uint8_t - byte of data to write to the LCD
 *
 *  returns: void
 */

void lcd_write_data(uint8_t);



/*
 * Function:  lcd_read_data
 * --------------------
 * Returns the HD44780 data register
 *
 *  
 *
 *  returns: (uint8_t) data register
 */

uint8_t lcd_read_data(void);



/*
 * Function:  lcd_print_text
 * --------------------
 * Writes a string to the LCD
 *
 *  char* - pointer to the string to write
 *
 *  returns: void
 */

void lcd_print_text(char *);



/*
 * Function:  lcd_go_to
 * --------------------
 * Moves the cursor to the x'th column and y'th line
 *
 *  1. uint8_t - column number (0 to 16)
 *  2. uint8_t - line number (0 to 1)
 *
 *  returns: void
 */

void lcd_go_to(uint8_t, uint8_t);



/*
 * Function:  lcd_clear
 * --------------------
 * Clears the LCD screen.
 *
 *  
 *
 *  returns: void
 */

void lcd_clear(void);



/*
 * Function:  lcd_home
 * --------------------
 * Moves the cursor to the beginning of the LCD screen (1st line, 1st column)
 *
 *  
 *
 *  returns: void
 */

void lcd_home(void);



/*
 * Function:  lcd_init
 * --------------------
 * Initialises Arduino UNO pins and enables the HD44780.
 *
 *  
 *
 *  returns: void
 */

void lcd_init(void);



/*
 * Function:  lcd_printf
 * --------------------
 * Formats data to a string and then prints it to the LCD.
 *
 *  const char *format - string format
 *
 *  returns: void
 */

void lcd_printf(const char *format, ...);
