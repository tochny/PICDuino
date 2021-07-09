/* 
 * File:   LiquidCrystal.c
 * Author: Alex Chih
 *
 * Created on 2016年7月
 */

#include "LiquidCrystal.h"


//<editor-fold defaultstate="collapsed" desc="LiquidCrystal">

// if RW = 255, The RW pin is not used.
void lcd_init(Byte RS, Byte RW, Byte EN, Byte DB0, Byte DB1, Byte DB2, Byte DB3)
{

    lcd.RS = RS;
    lcd.RW = RW;
    lcd.EN = EN;
    lcd.DB[0] = DB0;
    lcd.DB[1] = DB1;
    lcd.DB[2] = DB2;
    lcd.DB[3] = DB3;

    //    if (1)
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
    //    else
    //        _displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;

    lcd_begin(16, 1);
}

void lcd_begin(Byte cols, Byte lines)
{
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

    if (lines > 1)
        _displayfunction |= LCD_2LINE;

    _numlines = lines;

    lcd_setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

    // for some 1 line displays you can select a 10 pixel high font

    pinMode(lcd.RS, OUTPUT);
    if (lcd.RW != 255)
        pinMode(lcd.RW, OUTPUT);
    pinMode(lcd.EN, OUTPUT);

    // Do these once, instead of every time a character is drawn for speed reasons.
    for (int i = 0; i < ((_displayfunction & LCD_8BITMODE) ? 8 : 4); ++i)
        pinMode(lcd.DB[i], OUTPUT);

    // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    // according to datasheet, we need at least 40ms after power rises above 2.7V
    // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
    __delay_ms(5);
    // Now we pull both RS and R/W low to begin commands
    digitalWrite(lcd.RS, LOW);
    if (lcd.RW != 255)
        digitalWrite(lcd.RW, LOW);
    digitalWrite(lcd.EN, LOW);

    //put the LCD into 4 bit or 8 bit mode
    if (!(_displayfunction & LCD_8BITMODE))
    {
        // this is according to the hitachi HD44780 datasheet
        // figure 24, pg 46

        // we start in 8bit mode, try to set 4 bit mode
        lcd_write4bits(0x03);
        __delay_us(4500); // wait min 4.1ms

        // second try
        lcd_write4bits(0x03);
        __delay_us(4500); // wait min 4.1ms

        // third go!
        lcd_write4bits(0x03);
        __delay_us(150);

        // finally, set to 4-bit interface
        lcd_write4bits(0x02);
    }
    else
    {
        // this is according to the hitachi HD44780 datasheet
        // page 45 figure 23

        // Send function set command sequence

        lcd_command(LCD_FUNCTIONSET | _displayfunction);
        __delay_us(4500); // wait more than 4.1ms

        // second try
        lcd_command(LCD_FUNCTIONSET | _displayfunction);
        __delay_us(150);

        // third go
        lcd_command(LCD_FUNCTIONSET | _displayfunction);
    }

    // finally, set # lines, font size, etc.
    lcd_command(LCD_FUNCTIONSET | _displayfunction);

    // turn the display on with no cursor or blinking default
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    lcd_display();

    // clear it off
    lcd_clear();

    // Initialize to default text direction (for romance languages)
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    lcd_command(LCD_ENTRYMODESET | _displaymode);
}

void lcd_print(String string)
{
    while (string[0])
    {

        lcd_write(string[0]);
        string++;
    }
}

void lcd_setRowOffsets(int row0, int row1, int row2, int row3)
{

    _row_offsets[0] = row0;
    _row_offsets[1] = row1;
    _row_offsets[2] = row2;
    _row_offsets[3] = row3;
}

/********** high level commands, for the user! */
void lcd_clear()
{

    lcd_command(LCD_CLEARDISPLAY); // clear display, set cursor position to zero
    __delay_us(2000); // this command takes a long time!
}

void lcd_home()
{

    lcd_command(LCD_RETURNHOME); // set cursor position to zero
    __delay_us(2000); // this command takes a long time!
}

void lcd_setCursor(Byte col, Byte row)
{
    const Byte max_lines = sizeof (_row_offsets) / sizeof (*_row_offsets);
    if (row >= max_lines)
        row = max_lines - 1; // we count rows starting w/0

    if (row >= _numlines)
        row = _numlines - 1; // we count rows starting w/0

    lcd_command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

// Turn the display on/off (quickly)

void lcd_noDisplay()
{

    _displaycontrol &= ~LCD_DISPLAYON;
    lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void lcd_display()
{

    _displaycontrol |= LCD_DISPLAYON;
    lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off

void lcd_noCursor()
{

    _displaycontrol &= ~LCD_CURSORON;
    lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void lcd_cursor()
{

    _displaycontrol |= LCD_CURSORON;
    lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor

void lcd_noBlink()
{

    _displaycontrol &= ~LCD_BLINKON;
    lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void lcd_blink()
{

    _displaycontrol |= LCD_BLINKON;
    lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM

void lcd_scrollDisplayLeft(void)
{

    lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void lcd_scrollDisplayRight(void)
{

    lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right

void lcd_leftToRight(void)
{

    _displaymode |= LCD_ENTRYLEFT;
    lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left

void lcd_rightToLeft(void)
{

    _displaymode &= ~LCD_ENTRYLEFT;
    lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor

void lcd_autoscroll(void)
{

    _displaymode |= LCD_ENTRYSHIFTINCREMENT;
    lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor

void lcd_noAutoscroll(void)
{

    _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters

void lcd_createChar(Byte location, Byte charmap[])
{
    location &= 0x7; // we only have 8 locations 0-7
    lcd_command(LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++)
    {

        lcd_write(charmap[i]);
    }
}

/*********** mid level commands, for sending data/cmds */

inline void lcd_command(Byte value)
{

    lcd_send(value, LOW);
}

inline Byte lcd_write(Byte value)
{

    lcd_send(value, HIGH);
    return 1; // assume sucess
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection

void lcd_send(Byte value, Byte mode)
{
    digitalWrite(lcd.RS, mode);

    if (lcd.RW != 255)
        digitalWrite(lcd.RW, LOW);

    if (_displayfunction & LCD_8BITMODE)
    {
        lcd_write8bits(value);
    }
    else
    {

        lcd_write4bits(value >> 4);
        lcd_write4bits(value);
    }
}

void lcd_pulseEnable(void)
{

    digitalWrite(lcd.EN, LOW);
    __delay_us(1);
    digitalWrite(lcd.EN, HIGH);
    __delay_us(1); // enable pulse must be >450ns
    digitalWrite(lcd.EN, LOW);
    __delay_us(100); // commands need > 37us to settle
}

void lcd_write4bits(Byte value)
{

    for (int i = 0; i < 4; i++)
        digitalWrite(lcd.DB[i], (value >> i) & 0x01);

    lcd_pulseEnable();
}

void lcd_write8bits(Byte value)
{

    for (int i = 0; i < 8; i++)
        digitalWrite(lcd.DB[i], (value >> i) & 0x01);

    lcd_pulseEnable();
}

//</editor-fold>