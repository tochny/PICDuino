/* 
 * File:   Wire.c
 * Author: Alex Chih
 *
 * Created on 2016年7月
 */

#include "Wire.h"

void Wire_begin()
{
    TRISBbits.TRISB0 = INPUT; // SDA = INPUT
    TRISBbits.TRISB1 = INPUT;
    OpenI2C(MASTER, SLEW_OFF);
    SSPADD = ((_XTAL_FREQ / 4) / 100000) - 1;
    
}

void Wire_beginTransmission(Byte DevAddress)
{
    IdleI2C();
    StartI2C();
    IdleI2C();
    WriteI2C(DevAddress << 1 | 0x00);
}

void Wire_endTransmission()
{
    IdleI2C();
    StopI2C();
}

Byte Wire_read(Byte DevAddress, Byte RegAddress)
{
    Byte data;
    IdleI2C();
    WriteI2C(RegAddress);

    // R
    IdleI2C();
    RestartI2C();

    // Device read address
    IdleI2C();
    WriteI2C(DevAddress << 1 | 0x01);

    IdleI2C();
    data = ReadI2C();

    IdleI2C();
    NotAckI2C();

    return data;
}

void Wire_write(Byte data)
{
    IdleI2C();
    WriteI2C(data);
}

void Wire_end()
{
    CloseI2C();
}