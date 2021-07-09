/* 
 * File:   LiquidCrystal_I2C.h
 * Author: Alex Chih
 *
 * Created on 2016年7月28日, 下午 3:37
 */

#ifndef LIQUIDCRYSTAL_I2C_H
#define	LIQUIDCRYSTAL_I2C_H
#include "UniversalLib.h"
#include "Wire.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100  // Enable bit
#define Rw 0b00000010  // Read/Write bit
#define Rs 0b00000001  // Register select bit


Byte _displayfunction = 0;
Byte _displaycontrol = 0;
Byte _displaymode = 0;
Byte _initialized = 0;
Byte _numlines = 0;
Byte _row_offsets[4];
Byte _backlightval;
Byte _Addr;


void lcd_init(Byte address);
void lcd_begin(Byte cols, Byte lines);
void lcd_print(String);
void lcd_clear();
void lcd_home();
void lcd_noDisplay();
void lcd_display();
void lcd_noBlink();
void lcd_blink();
void lcd_noCursor();
void lcd_cursor();
void lcd_scrollDisplayLeft();
void lcd_scrollDisplayRight();
void lcd_leftToRight();
void lcd_rightToLeft();
void lcd_autoscroll();
void lcd_noAutoscroll();
void lcd_setRowOffsets(int row1, int row2, int row3, int row4);
void lcd_createChar(Byte, Byte[]);
void lcd_setCursor(Byte, Byte);
void lcd_backlight();
void lcd_noBacklight();

inline Byte lcd_write(Byte);
inline void lcd_command(Byte);
void expanderWrite(Byte);

void lcd_send(Byte, Byte);
void lcd_write4bits(Byte);
void lcd_pulseEnable(Byte);


#endif	/* LIQUIDCRYSTAL_I2C_H */

