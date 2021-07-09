/* 
 * File:   OneWire.c
 * Author: Alex Chih
 *
 * Created on 2016年7月
 */

#include "OneWire.h"

//<editor-fold defaultstate="collapsed" desc="OneWire">

static void OneWireLow(Byte DQpin)
{
    digitalWrite(DQpin, LOW);
    pinMode(DQpin, OUTPUT);
}

static void OneWireHigh(Byte DQpin)
{
    pinMode(DQpin, INPUT);
}

/*  
 *  Initiates the one wire bus
 *  Performs a reset on the one-wire bus and returns the presence detect.
 *  Reset is 2*480us long, presence checked another 60us later.
 *  returns 0=presence, 1=no part
 */

Byte OneWireReset(Byte DQpin)
{
    Byte presence;

    OneWireLow(DQpin); // pull DQ line low
    delay100us();delay100us();delay100us();delay100us();delay10us();delay10us();delay10us();delay10us();delay10us();delay10us();delay10us();delay10us(); // leave it low for min. 480us
    OneWireHigh(DQpin); // allow line to return high
    delay10us();delay10us();delay10us();delay10us();delay10us(); // takes 15 to 60 us
    presence = digitalRead(DQpin); // get presence signal
    delay100us();delay100us();delay100us();delay100us();delay10us();delay10us(); // wait for end of timeslot (960-480-60=420)
    return presence;
}

/*	----------------------------------------------------------------------------
        ---------- Read a bit from the one-wire bus and return it.
        --------------------------------------------------------------------------*/

Byte OneWireReadBit(Byte DQpin)
{
    Byte dq;

    OneWireLow(DQpin); // pull DQ line low to start time slot
    //myDelay_us(1);				// 1us
    OneWireHigh(DQpin); // allow line to return high
    //myDelay_us(5);					// Read within 15uS from start of time slot
    dq = digitalRead(DQpin); // get presence signal
    delay10us();delay10us();delay10us();delay10us();delay10us(); // wait for rest of timeslot
    return (dq); // return value of DQ line
}

/*	----------------------------------------------------------------------------
        ---------- Read a byte from the one-wire bus and return it.
        --------------------------------------------------------------------------*/

Byte OneWireRead(Byte DQpin)
{
    Byte i, value = 0;
    for (i = 0; i < 8; i++)
    {
        if (OneWireReadBit(DQpin)) // reads byte in, one bit at a time
        {
            value |= 0x01 << i; // and then shifts it left
        }
    }
    return (value);
}

/*	----------------------------------------------------------------------------
        ---------- Writes a bit to the one-wire bus, passed in bitval.
        --------------------------------------------------------------------------*/

void OneWireWriteBit(Byte DQpin, Byte bitval)
{
    if (bitval == 1)
    {
        OneWireLow(DQpin); // pull DQ line low
        //myDelay_us(5);					// for max. 15us
        OneWireHigh(DQpin); // allow line to return high
        delay10us();delay10us();delay10us();delay10us();delay10us();delay10us();
    }
    else
    {
        OneWireLow(DQpin); // pull DQ line low
        delay10us();delay10us();delay10us();delay10us();delay10us();delay10us(); // for the whole time slot
        OneWireHigh(DQpin); // allow line to return high
    }
}

/*	----------------------------------------------------------------------------
        ---------- Writes a byte to the one-wire bus.
        --------------------------------------------------------------------------*/

void OneWireWrite(Byte DQpin, Byte val)
{
    Byte i, temp;
    for (i = 0; i < 8; i++) // writes byte, one bit at a time
    {
        temp = val >> i; // shifts val right 'i' spaces
        temp &= 0x01; // copy that bit to temp
        OneWireWriteBit(DQpin, temp); // write bit in temp into
    }
}
//</editor-fold>