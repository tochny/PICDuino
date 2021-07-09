/* 
 * File:   DS1302.h - library support for the DS1302
 * Author: Alex Chih
 *
 * Created on 2016年7月31日, 上午 11:33
 */

#ifndef DS1302_H
#define	DS1302_H

#include "UniversalLib.h"


#define FORMAT_SHORT	1
#define FORMAT_LONG	2

#define FORMAT_LITTLEENDIAN	1
#define FORMAT_BIGENDIAN	2
#define FORMAT_MIDDLEENDIAN	3

#define MONDAY		1
#define TUESDAY		2
#define WEDNESDAY	3
#define THURSDAY	4
#define FRIDAY		5
#define SATURDAY	6
#define SUNDAY		7

#define TCR_D1R2K	165
#define TCR_D1R4K	166
#define TCR_D1R8K	167
#define TCR_D2R2K	169
#define TCR_D2R4K	170
#define TCR_D2R8K	171
#define TCR_OFF		92

typedef struct {
    Byte hour;
    Byte min;
    Byte sec;
    Byte date;
    Byte mon;
    UInt16 year;
    Byte dow;
} RTCTIME;

typedef struct {
    Byte cell[31];
} DS1302_RAM;

void RTC_begin(Byte ce_pin, Byte data_pin, Byte sclk_pin);
RTCTIME getTime();
void setTime(Byte hour, Byte min, Byte sec);
void setDate(Byte date, Byte mon, UInt16 year);
void setDOW(Byte dow);

char *getTimeStr(Byte format);
char *getDateStr(Byte slformat, Byte eformat, char divider);
char *getDOWStr(Byte format);
char *getMonthStr(Byte format);

void halt(bool value);
void writeProtect(bool enable);
void setTCR(Byte value);

void writeBuffer(DS1302_RAM r);
DS1302_RAM readBuffer();
void poke(Byte addr, Byte value);
Byte peek(Byte addr);

Byte _ce_pin;
Byte _data_pin;
Byte _sclk_pin;
Byte _burstArray[8];

Byte _readByte();
void _writeByte(Byte value);
Byte _readRegister(Byte reg);
void _writeRegister(Byte reg, Byte value);
void _burstRead();
Byte _decode(Byte value);
Byte _decodeH(Byte value);
Byte _decodeY(Byte value);
Byte _encode(Byte vaule);


#endif	/* DS1302_H */

