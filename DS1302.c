/*
 * File:   DS1302.c - library support for the DS1302
 * Author: Alex Chih
 *
 * Created on 2016年7月31日, 上午 11:33
 */


#include "DS1302.h"

#define REG_SEC		0
#define REG_MIN		1
#define REG_HOUR	2
#define REG_DATE	3
#define REG_MON		4
#define REG_DOW		5
#define REG_YEAR	6
#define REG_WP		7
#define REG_TCR		8

void RTC_begin(Byte ce_pin, Byte data_pin, Byte sclk_pin)
{
    RTCTIME t;
    t.year = 2016;
    t.mon = 7;
    t.date = 31;
    t.hour = 0;
    t.min = 0;
    t.sec = 0;
    t.dow = 5;

    _ce_pin = ce_pin;
    _data_pin = data_pin;
    _sclk_pin = sclk_pin;

    pinMode(_ce_pin, OUTPUT);
    pinMode(_sclk_pin, OUTPUT);
}

RTCTIME getTime()
{
    RTCTIME t;
    _burstRead();
    t.sec = _decode(_burstArray[0]);
    t.min = _decode(_burstArray[1]);
    t.hour = _decodeH(_burstArray[2]);
    t.date = _decode(_burstArray[3]);
    t.mon = _decode(_burstArray[4]);
    t.dow = _burstArray[5];
    t.year = _decodeY(_burstArray[6]) + 2000;
    return t;
}

void setTime(Byte hour, Byte min, Byte sec)
{
    if (((hour >= 0) && (hour < 24)) && ((min >= 0) && (min < 60)) && ((sec >= 0) && (sec < 60)))
    {
        _writeRegister(REG_HOUR, _encode(hour));
        _writeRegister(REG_MIN, _encode(min));
        _writeRegister(REG_SEC, _encode(sec));
    }
}

void setDate(Byte date, Byte mon, UInt16 year)
{
    if (((date > 0) && (date <= 31)) && ((mon > 0) && (mon <= 12)) && ((year >= 2000) && (year < 3000)))
    {
        year -= 2000;
        _writeRegister(REG_YEAR, _encode(year));
        _writeRegister(REG_MON, _encode(mon));
        _writeRegister(REG_DATE, _encode(date));
    }
}

void setDOW(Byte dow)
{
    if ((dow > 0) && (dow < 8))
        _writeRegister(REG_DOW, dow);
}

char *getTimeStr(Byte format)
{
    char *output;
    RTCTIME t;
    t = getTime();
    if (t.hour < 10)
        output[0] = 48;
    else
        output[0] = (char)((t.hour / 10) + 48);
    output[1] = (char)((t.hour % 10) + 48);
    output[2] = 58;
    if (t.min < 10)
        output[3] = 48;
    else
        output[3] = (char)((t.min / 10) + 48);
    output[4] = (char)((t.min % 10) + 48);
    output[5] = 58;
    if (format == FORMAT_SHORT)
        output[5] = 0;
    else
    {
        if (t.sec < 10)
            output[6] = 48;
        else
            output[6] = (char)((t.sec / 10) + 48);
        output[7] = (char)((t.sec % 10) + 48);
        output[8] = 0;
    }
    return output;
}

char *getDateStr(Byte slformat, Byte eformat, char divider)
{
    char *output = "xxxxxxxxxx";
    int yr, offset;
    RTCTIME t;
    t = getTime();
    
    switch (eformat)
    {
    case FORMAT_LITTLEENDIAN:
        if (t.date < 10)
            output[0] = 48;
        else
            output[0] = (char)((t.date / 10) + 48);
        output[1] = (char)((t.date % 10) + 48);
        output[2] = divider;
        if (t.mon < 10)
            output[3] = 48;
        else
            output[3] = (char)((t.mon / 10) + 48);
        output[4] = (char)((t.mon % 10) + 48);
        output[5] = divider;
        if (slformat == FORMAT_SHORT)
        {
            yr = t.year - 2000;
            if (yr < 10)
                output[6] = 48;
            else
                output[6] = (char)((yr / 10) + 48);
            output[7] = (char)((yr % 10) + 48);
            output[8] = 0;
        }
        else
        {
            yr = t.year;
            output[6] = (char)((yr / 1000) + 48);
            output[7] = (char)(((yr % 1000) / 100) + 48);
            output[8] = (char)(((yr % 100) / 10) + 48);
            output[9] = (char)((yr % 10) + 48);
            output[10] = 0;
        }
        break;
    case FORMAT_BIGENDIAN:
        if (slformat == FORMAT_SHORT)
            offset = 0;
        else
            offset = 2;
        if (slformat == FORMAT_SHORT)
        {
            yr = t.year - 2000;
            if (yr < 10)
                output[0] = 48;
            else
                output[0] = (char)((yr / 10) + 48);
            output[1] = (char)((yr % 10) + 48);
            output[2] = divider;
        }
        else
        {
            yr = t.year;
            output[0] = (char)((yr / 1000) + 48);
            output[1] = (char)(((yr % 1000) / 100) + 48);
            output[2] = (char)(((yr % 100) / 10) + 48);
            output[3] = (char)((yr % 10) + 48);
            output[4] = divider;
        }
        if (t.mon < 10)
            output[3 + offset] = 48;
        else
            output[3 + offset] = (char)((t.mon / 10) + 48);
        output[4 + offset] = (char)((t.mon % 10) + 48);
        output[5 + offset] = divider;
        if (t.date < 10)
            output[6 + offset] = 48;
        else
            output[6 + offset] = (char)((t.date / 10) + 48);
        output[7 + offset] = (char)((t.date % 10) + 48);
        output[8 + offset] = 0;
        break;
    case FORMAT_MIDDLEENDIAN:
        if (t.mon < 10)
            output[0] = 48;
        else
            output[0] = (char)((t.mon / 10) + 48);
        output[1] = (char)((t.mon % 10) + 48);
        output[2] = divider;
        if (t.date < 10)
            output[3] = 48;
        else
            output[3] = (char)((t.date / 10) + 48);
        output[4] = (char)((t.date % 10) + 48);
        output[5] = divider;
        if (slformat == FORMAT_SHORT)
        {
            yr = t.year - 2000;
            if (yr < 10)
                output[6] = 48;
            else
                output[6] = (char)((yr / 10) + 48);
            output[7] = (char)((yr % 10) + 48);
            output[8] = 0;
        }
        else
        {
            yr = t.year;
            output[6] = (char)((yr / 1000) + 48);
            output[7] = (char)(((yr % 1000) / 100) + 48);
            output[8] = (char)(((yr % 100) / 10) + 48);
            output[9] = (char)((yr % 10) + 48);
            output[10] = 0;
        }
        break;
    }
    return output;
}

char *getDOWStr(Byte format)
{
    char *output = "xxxxxxxxx";
    RTCTIME t;
    t = getTime();
    switch (t.dow)
    {
    case MONDAY:
        output = "Monday";
        break;
    case TUESDAY:
        output = "Tuesday";
        break;
    case WEDNESDAY:
        output = "Wednesday";
        break;
    case THURSDAY:
        output = "Thursday";
        break;
    case FRIDAY:
        output = "Friday";
        break;
    case SATURDAY:
        output = "Saturday";
        break;
    case SUNDAY:
        output = "Sunday";
        break;
    }
    if (format == FORMAT_SHORT)
        output[3] = 0;
    return output;
}

char *getMonthStr(Byte format)
{
    char *output;
    RTCTIME t;
    switch (t.mon)
    {
    case 1:
        output = "January";
        break;
    case 2:
        output = "February";
        break;
    case 3:
        output = "March";
        break;
    case 4:
        output = "April";
        break;
    case 5:
        output = "May";
        break;
    case 6:
        output = "June";
        break;
    case 7:
        output = "July";
        break;
    case 8:
        output = "August";
        break;
    case 9:
        output = "September";
        break;
    case 10:
        output = "October";
        break;
    case 11:
        output = "November";
        break;
    case 12:
        output = "December";
        break;
    }
    if (format == FORMAT_SHORT)
        output[3] = 0;
    return output;
}

void halt(bool enable)
{
    Byte _reg = _readRegister(REG_SEC);
    _reg &= ~(1 << 7);
    _reg |= (enable << 7);
    _writeRegister(REG_SEC, _reg);
}

void writeProtect(bool enable)
{
    Byte _reg = (enable << 7);
    _writeRegister(REG_WP, _reg);
}

void setTCR(Byte value)
{
    _writeRegister(REG_TCR, value);
}

/* Private */

Byte _readByte()
{
    pinMode(_data_pin, INPUT);

    Byte value = 0;
    Byte currentBit = 0;

    for (int i = 0; i < 8; ++i)
    {
        currentBit = digitalRead(_data_pin);
        value |= (currentBit << i);
        digitalWrite(_sclk_pin, HIGH);
        delayMicroseconds(1);
        digitalWrite(_sclk_pin, LOW);
    }
    return value;
}

void _writeByte(Byte value)
{
    pinMode(_data_pin, OUTPUT);
    shiftOut(_data_pin, _sclk_pin, LSBFIRST, value);
}

Byte _readRegister(Byte reg)
{
    Byte cmdByte = 129;
    cmdByte |= (reg << 1);

    Byte readValue;

    digitalWrite(_sclk_pin, LOW);
    digitalWrite(_ce_pin, HIGH);

    _writeByte(cmdByte);
    readValue = _readByte();

    digitalWrite(_ce_pin, LOW);

    return readValue;
}

void _writeRegister(Byte reg, Byte value)
{
    Byte cmdByte = (128 | (reg << 1));

    digitalWrite(_sclk_pin, LOW);
    digitalWrite(_ce_pin, HIGH);

    _writeByte(cmdByte);
    _writeByte(value);

    digitalWrite(_ce_pin, LOW);
}

void _burstRead()
{
    digitalWrite(_sclk_pin, LOW);
    digitalWrite(_ce_pin, HIGH);

    _writeByte(191);
    for (int i = 0; i < 8; i++)
    {
        _burstArray[i] = _readByte();
    }
    digitalWrite(_ce_pin, LOW);
}

Byte _decode(Byte value)
{
    Byte decoded = value & 127;
    decoded = (decoded & 15) + 10 * ((decoded & (15 << 4)) >> 4);
    return decoded;
}

Byte _decodeH(Byte value)
{
    if (value & 128)
        value = (value & 15) + (12 * ((value & 32) >> 5));
    else
        value = (value & 15) + (10 * ((value & 48) >> 4));
    return value;
}

Byte _decodeY(Byte value)
{
    Byte decoded = (value & 15) + 10 * ((value & (15 << 4)) >> 4);
    return decoded;
}

Byte _encode(Byte value)
{
    Byte encoded = ((value / 10) << 4) + (value % 10);
    return encoded;
}

void writeBuffer(DS1302_RAM r)
{
    digitalWrite(_sclk_pin, LOW);
    digitalWrite(_ce_pin, HIGH);

    _writeByte(254);
    for (int i = 0; i < 31; i++)
    {
        _writeByte(r.cell[i]);
    }
    digitalWrite(_ce_pin, LOW);
}

DS1302_RAM readBuffer()
{
    DS1302_RAM r;

    digitalWrite(_sclk_pin, LOW);
    digitalWrite(_ce_pin, HIGH);

    _writeByte(255);
    for (int i = 0; i < 31; i++)
    {
        r.cell[i] = _readByte();
    }
    digitalWrite(_ce_pin, LOW);

    return r;
}

void poke(Byte addr, Byte value)
{
    if ((addr >= 0) && (addr <= 30))
    {
        addr = (addr * 2) + 192;

        digitalWrite(_sclk_pin, LOW);
        digitalWrite(_ce_pin, HIGH);

        _writeByte(addr);
        _writeByte(value);

        digitalWrite(_ce_pin, LOW);
    }
}

Byte peek(Byte addr)
{
    if ((addr >= 0) && (addr <= 30))
    {
        addr = (addr * 2) + 193;

        Byte readValue;

        digitalWrite(_sclk_pin, LOW);
        digitalWrite(_ce_pin, HIGH);

        _writeByte(addr);
        readValue = _readByte();

        digitalWrite(_ce_pin, LOW);

        return readValue;
    }
    else
        return 0;
}
