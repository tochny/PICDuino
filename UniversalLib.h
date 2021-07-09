/* 
 * File:   UniversalLib.h
 * Author: Alex Chih
 *
 * Created on 2016年7月2日, 下午 12:21
 */

#ifndef UNIVERSALLIB_H
#define	UNIVERSALLIB_H

// <editor-fold defaultstate="collapsed" desc="Definition & Global Value">
#define USE_AND_MASKS
#define _XTAL_FREQ 48000000 //The speed of internal clock
#define _TMR1ms_
//#define _TMR100us_
#define forever for(;;)

#define HIGH 1
#define LOW 0

#define INPUT 1
#define OUTPUT 0

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define A0 24
#define A1 25
#define A2 26
#define A3 27
#define DEFAULT 0
#define EXTERNAL 1

#define PWM0 32
#define PWM1 33

#define ComplexPort
#ifdef ComplexPort
#define TIO0 TRISDbits.TRISD0
#define TIO1 TRISDbits.TRISD1
#define TIO2 TRISDbits.TRISD2
#define TIO3 TRISDbits.TRISD3
#define TIO4 TRISDbits.TRISD4
#define TIO5 TRISDbits.TRISD5
#define TIO6 TRISDbits.TRISD6
#define TIO7 TRISDbits.TRISD7
#define TIO8 TRISBbits.TRISB0
#define TIO9 TRISBbits.TRISB1
#define TIO10 TRISBbits.TRISB2
#define TIO11 TRISBbits.TRISB3
#define TIO12 TRISBbits.TRISB4
#define TIO13 TRISBbits.TRISB5
#define TIO14 TRISBbits.TRISB6
#define TIO15 TRISBbits.TRISB7
#define TIO16 TRISEbits.TRISE0
#define TIO17 TRISEbits.TRISE1
#define TIO18 TRISEbits.TRISE2
#define RBPULLUP INTCON2bits.RBPU

#define IO0 PORTDbits.RD0
#define IO1 PORTDbits.RD1
#define IO2 PORTDbits.RD2
#define IO3 PORTDbits.RD3
#define IO4 PORTDbits.RD4
#define IO5 PORTDbits.RD5
#define IO6 PORTDbits.RD6
#define IO7 PORTDbits.RD7
#define IO8 PORTBbits.RB0
#define IO9 PORTBbits.RB1
#define IO10 PORTBbits.RB2
#define IO11 PORTBbits.RB3
#define IO12 PORTBbits.RB4
#define IO13 PORTBbits.RB5
#define IO14 PORTBbits.RB6
#define IO15 PORTBbits.RB7
#define IO16 PORTEbits.RE0
#define IO17 PORTEbits.RE1
#define IO18 PORTEbits.RE2

#endif


typedef char* String;

char RX_DONE = 0;
#define Serial_available() RX_DONE

unsigned long _time_ = 0;
#define millis() _time_

#ifdef _TMR100us_
#define TH 0xFB
#define TL 0x50
#endif

#ifdef _TMR1ms_
#define TH 0xD1
#define TL 0x20
#endif
//</ editor-fold>

// <editor-fold defaultstate="collapsed" desc="Includes">
#include <xc.h>
#include "config.h"
#include "ints.h" 
#include <plib/usart.h>
#include <math.h>
#include <stdbool.h>
//</editor-fold>

void sei();

void delay10us(void);
void delay100us(void);
void delay(unsigned int);
#define delayMicroseconds(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))


void timer0init(void); // necessary

void analoginit(void); // necessary
int analogRead(char);
void SetPWMFrequency(double);
void analogWrite(char, double);
void analogReference(char);

unsigned long pulseIn(char*, char, char);
void servoinit();

void pinMode(char, char);
inline void digitalWrite(char, char);
inline char digitalRead(char);

Byte shiftIn(Byte dataPin, Byte clockPin, Byte bitOrder);
void shiftOut(Byte dataPin, Byte clockPin, Byte bitOrder, Byte val);


float Serial_begin(unsigned long); // necessary
void Serial_print(String);
void Serial_println(String);
void Serial_write(char);
String Serial_read();


void PutNumber(char array[16][16], char num[5][7], int offsetX, int offsetY);
double map(double x, double i_min, double i_max, double o_min, double o_max);

String Int32ToString(Int32);
Int32 StringToInt32(String);
String Int16ToString(Int16);
String ByteToString(Byte);

String String_Add(String, String);
String String_Substring(String, Int32, Int32);
String String_Left(String, Int32);


#endif	/* UNIVERSALLIB_H */