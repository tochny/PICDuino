/* 
 * File:   DS18B20.h
 * Author: Alex Chih
 *
 * Created on 2016年7月22日, 下午 4:11
 */

#ifndef DS18B20_H
#define	DS18B20_H

#include "UniversalLib.h"
#include "OneWire.h"

typedef struct
{
    Byte sign; // sign (1=negative)
    Byte integer; // integer part
    Int16 fraction; // fractional part
} DS18B20_Temperature;

/*	----------------------------------------------------------------------------
    ---------- GLOBAL VARIABLES
    --------------------------------------------------------------------------*/

Byte DS18B20Rom[6][8]; // table of found ROM codes
Byte ROM[8]; // ROM Bit
Byte lastDiscrep = 0; // last discrepancy
Byte doneFlag = 0; // Done flag
Byte numROMs;
Byte dowcrc;

/*
const Byte dscrc_table[] = {
    0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
    157,195, 33,127,252,162, 64, 30, 95, 1,227,189, 62, 96,130,220,
    35,125,159,193, 66, 28,254,160,225,191, 93, 3,128,222, 60, 98,
    190,224, 2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
    70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89, 7,
    219,133,103, 57,186,228, 6, 88, 25, 71,165,251,120, 38,196,154,
    101, 59,217,135, 4, 90,184,230,167,249, 27, 69,198,152,122, 36,
    248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91, 5,231,185,
    140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
    17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
    175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
    50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
    202,148,118, 40,171,245, 23, 73, 8, 86,180,234,105, 55,213,139,
    87, 9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
    233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
    116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53};
 */

/// DS18B20 ROM COMMANDS

#define SEARCHROM			0xF0	//
#define READROM				0x33	//
#define MATCHROM			0x55	//
#define SKIPROM				0xCC	//
#define ALARM_SEARCH		0xEC	//

/// DS18B20 FUNCTION COMMANDS

#define CONVERT_T			0x44	// Initiates temperature conversion
#define WRITE_SCRATCHPAD	0x4E	// Writes data into scratchpad bytes 2, 3, and 4 (TH, TL and configuration registers)
#define READ_SCRATCHPAD		0xBE	// Reads the entire scratchpad including the CRC byte
#define COPY_SCRATCHPAD		0x48	// Copies TH, TL, and configuration register data from the scratchpad to EEPROM
#define RECALL_E2			0xB8	// Recalls TH, TL, and configuration register data from EEPROM to the scratchpad
#define READ_POWER_SUPPLY	0xB4	// Signals DS18B20 power supply mode to the master

/// MODES

#define RES12BIT			1		// 12-bit resolution (slowest mode)
#define RES11BIT			2		// 11-bit resolution
#define RES10BIT			3		// 10-bit resolution
#define  RES9BIT			4		//  9-bit resolution (quickest mode)

/// PROTOTYPES

Byte DS18B20Read(Byte, Byte, Byte, DS18B20_Temperature *);
Byte DS18B20MatchRom(Byte, Byte);
void DS18B20ReadRom(Byte, Byte *);
Byte DS18B20Configure(Byte, Byte, Byte, Byte, Byte);
void DS18B20Find(Byte);
Byte DS18B20GetFirst(Byte);
Byte DS18B20GetNext(Byte);
Byte DS18B20_crc(Byte);
Byte DS18B20StartMeasure(Byte pin, Byte mem, Byte resolution);
Byte DS18B20ReadMeasure(Byte pin, Byte mem, DS18B20_Temperature * t);

/*	----------------------------------------------------------------------------
    ---------- DS18B20Read()
    ----------------------------------------------------------------------------
 * Description:	reads the ds18x20 device on the 1-wire bus and returns the temperature
 * Arguments:	pin = pin number where one wire bus is connected.
                    rom = index of the sensor or SKIPROM
                    resolution = 9 to 12 bit resolution
                    t = temperature pointer
    --------------------------------------------------------------------------*/

Byte DS18B20Read(Byte pin, Byte mem, Byte resolution, DS18B20_Temperature * t) {
    Byte res, busy = LOW;
    Byte temp_lsb, temp_msb;
    Int16 temp;

    switch (resolution) {
        case RES12BIT: res = 0b01100000;
            break; // 12-bit resolution
        case RES11BIT: res = 0b01000000;
            break; // 11-bit resolution
        case RES10BIT: res = 0b00100000;
            break; // 10-bit resolution
        case RES9BIT: res = 0b00000000;
            break; //  9-bit resolution
        default: res = 0b00000000;
            break; //  9-bit resolution
            /// NB: The power-up default of these bits is R0 = 1 and R1 = 1 (12-bit resolution)
    }

    if (!DS18B20Configure(pin, mem, 0, 0, res)) return 0; // no alarm

    if (OneWireReset(pin)) return 0;

    if (mem == SKIPROM) {
        // Skip ROM, address all devices
        OneWireWrite(pin, SKIPROM);
    } else {
        // Talk to a particular device
        if (!DS18B20MatchRom(pin, mem)) return 0;
    }

    OneWireWrite(pin, CONVERT_T); // Start temperature conversion

    while (busy == LOW) // Wait while busy ( = bus is low)
        busy = OneWireRead(pin);

    if (OneWireReset(pin)) return 0;

    if (mem == SKIPROM) {
        // Skip ROM, address all devices
        OneWireWrite(pin, SKIPROM);
    } else {
        // Talk to a particular device
        if (!DS18B20MatchRom(pin, mem)) return 0;
    }

    OneWireWrite(pin, READ_SCRATCHPAD); // Read scratchpad

    temp_lsb = OneWireRead(pin); // byte 0 of scratchpad : temperature lsb
    temp_msb = OneWireRead(pin); // byte 1 of scratchpad : temperature msb

    if (OneWireReset(pin)) return 0;

    // Calculation
    // ---------------------------------------------------------------------
    //	Temperature Register Format
    //			BIT7	BIT6	BIT5	BIT4	BIT3	BIT2	BIT1	BIT0
    //	LS BYTE 2^3		2^2		2^1		2^0		2^-1	2^-2	2^-3	2^-4
    //			BIT15	BIT14	BIT13	BIT12	BIT11	BIT10	BIT9	BIT8
    //	MS BYTE S		S		S		S		S		2^6		2^5 	2^4
    //	S = SIGN

    temp = temp_msb;
    temp = (temp << 8) + temp_lsb; // combine msb & lsb into 16 bit variable

    if (temp_msb & 0b11111000) // test if sign is set, i.e. negative
    {
        t->sign = 1;
        temp = (temp ^ 0xFFFF) + 1; // 2's complement conversion
    } else {
        t->sign = 0;
    }

    t->integer = (temp >> 4) & 0x7F; // fractional part is removed, leaving only integer part

    /*	
            t->fraction = 0;					// fractional part
            if (BitRead(temp, 0)) t->fraction +=  625;
            if (BitRead(temp, 1)) t->fraction += 1250;
            if (BitRead(temp, 2)) t->fraction += 2500;
            if (BitRead(temp, 3)) t->fraction += 5000;
     */
    t->fraction = (temp & 0x0F) * 625;
    t->fraction /= 100; // two digits after decimal 

    return 1;
}

/*	----------------------------------------------------------------------------
    ---------- DS18B20Configure()
    ----------------------------------------------------------------------------
 * Description: writes configuration data to the DS18x20 device
 * Arguments:
                    pin = pin number where one wire bus is connected.
                    rom = index of the sensor
                    TH = Alarm Trigger High
                    TL = Alarm Trigger Low
                    config = configuration
 * Data must be transmitted least significant bit first
    --------------------------------------------------------------------------*/

Byte DS18B20Configure(Byte pin, Byte mem, Byte h, Byte l, Byte conf) {
    if (OneWireReset(pin)) return 0;

    if (mem == SKIPROM) {
        // Skip ROM, address all devices
        OneWireWrite(pin, SKIPROM);
    }

    else {
        // Talk to a particular device
        DS18B20MatchRom(pin, mem);
    }
    OneWireWrite(pin, WRITE_SCRATCHPAD); // Allows the master to write 3 bytes of data to the scratchpad
    OneWireWrite(pin, h); // The first data byte is written into the TH register (byte 2 of the scratchpad)
    OneWireWrite(pin, l); // The second byte is written into the TL register (byte 3)
    OneWireWrite(pin, conf); // The third byte is written into the configuration register (byte 4)
    return 1;
}

/*	----------------------------------------------------------------------------
    ---------- Address a specific slave device on a multidrop or single-drop bus
    ----------------------------------------------------------------------------
 * Arguments:	pin = pin number where one wire bus is connected.
                    mem = index of the sensor
 * Description:	reads and returns a byte of data from the device.
    ----------------------------------------------------------------------------
    The match ROM command followed by a 64-bit ROM code sequence allows the bus
    master to address a specific slave device on a multidrop or single-drop bus.
    Only the slave that exactly matches the 64-bit ROM code sequence will respond
    to the function command issued by the master; all other slaves on the bus
    will wait for a reset pulse.
    --------------------------------------------------------------------------*/

Byte DS18B20MatchRom(Byte pin, Byte mem) {
    Byte i;
    if (OneWireReset(pin)) return 0;
    OneWireWrite(pin, MATCHROM); // Match Rom
    for (i = 0; i < 8; i++) // Send the Address ROM Code.
        OneWireWrite(pin, DS18B20Rom[mem][i]);
    return 1;
}

/*	----------------------------------------------------------------------------
    ---------- Reads the ROM Code from a device (when there is only one)
    ----------------------------------------------------------------------------
 * Arguments:	pin = pin number where one wire bus is connected.
                    romcode = identification code of device.
 * Description: reads and returns a byte of data from the device.
    ----------------------------------------------------------------------------
    This command can only be used when there is only ONE slave on the bus.
    It allows the bus master to read the slave’s 64-bit ROM code without using the Search ROM procedure.
    If this command is used when there is more than one slave present on the bus,
    a data collision will occur when all the slaves attempt to respond at the same time.
    --------------------------------------------------------------------------*/

void DS18B20ReadRom(Byte pin, Byte *romcode) {
    Byte i;
    if (!OneWireReset(pin)) {
        OneWireWrite(pin, READROM);
        for (i = 0; i < 8; i++) // Reads the ROM Code from a device
            romcode[i] = OneWireRead(pin);
    }
}

/*	----------------------------------------------------------------------------
    ---------- Find Devices on the one-wire bus
    ----------------------------------------------------------------------------
 * Arguments: pin number where one wire bus is connected.
 * Description: detects devices and print their rom code.
    --------------------------------------------------------------------------*/

void DS18B20Find(Byte pin) {
    Byte m;

    if (!OneWireReset(pin)) // Detects presence of devices
    {
        if (DS18B20GetFirst(pin)) // Begins when at least one part is found
        {
            numROMs = 0;
            do {
                numROMs++;
                // serialprint("Device #");
                for (m = 0; m < 8; m++) {
                    // Identifies ROM number on found device
                    DS18B20Rom[numROMs][m] = ROM[m];
                }
                //Continues until no additional devices are found
            } while (DS18B20GetNext(pin)&&(numROMs < 10));
        }
    }
}

/*	----------------------------------------------------------------------------
    ---------- First
    ----------------------------------------------------------------------------
 * Arguments: pin number where one wire bus is connected.
 * Description: resets the current state of a ROM search and calls Next to
    find the first device on the 1-wire bus.
    --------------------------------------------------------------------------*/

Byte DS18B20GetFirst(Byte pin) {
    lastDiscrep = 0; // reset the rom search last discrepancy global
    doneFlag = 0;
    return DS18B20GetNext(pin); // call Next and return its return value
}

/*	----------------------------------------------------------------------------
    ---------- Next
    ----------------------------------------------------------------------------
 * Arguments: pin number where one wire bus is connected.
 * Description: searches for the next device on the 1-wire bus. If
    there are no more devices on the 1-wire then 0 is returned.
    --------------------------------------------------------------------------*/

Byte DS18B20GetNext(Byte pin) {
    Byte m = 1; // ROM Bit index
    Byte n = 0; // ROM Byte index
    Byte k = 1; // bit mask
    Byte x = 0;
    Byte discrepMarker = 0; // discrepancy marker
    Byte g; // Output bit
    Byte nxt; // return value
    int flag;

    nxt = 0; // set the next flag to 0
    dowcrc = 0; // reset the dowcrc

    flag = OneWireReset(pin); // reset the 1-wire
    if (flag || doneFlag) // no parts -> return 0
    {
        lastDiscrep = 0; // reset the search
        return 0;
    }
    // send SearchROM command for all eight bytes
    OneWireWrite(pin, SEARCHROM);
    do {
        x = 0;
        if (OneWireReadBit(pin) == 1) x = 2;
        //myDelay_10us(12);
        if (OneWireReadBit(pin) == 1) x |= 1;
        if (x == 3)
            break;
        else {
            if (x > 0) // all devices coupled have 0 or 1
                g = x >> 1; // bit write value for search
            else {
                // if this discrepancy is before the last
                // discrepancy on a previous Next then pick
                // the same as last time
                if (m < lastDiscrep)
                    g = ((ROM[n] & k) > 0);
                else // if equal to last pick 1
                    g = (m == lastDiscrep); // if not then pick 0
                // if 0 was picked then record position with mask k
                if (g == 0) discrepMarker = m;
            }
            if (g == 1) // isolate bit in ROM[n] with mask k
                ROM[n] |= k;
            else
                ROM[n] &= ~k;
            OneWireWriteBit(pin, g); // ROM search write
            m++; // increment bit counter m
            k = k << 1; // and shift the bit mask k
            if (k == 0) // if the mask is 0 then go to new ROM
            { // byte n and reset mask
                DS18B20_crc(ROM[n]); // accumulate the CRC
                n++;
                k++;
            }
        }
    } while (n < 8); // loop until through all ROM bytes 0-7
    if (m < 65 || dowcrc) // if search was unsuccessful then
        lastDiscrep = 0; // reset the last discrepancy to 0
    else // search was successful, so set lastDiscrep, lastOne, nxt
    {
        lastDiscrep = discrepMarker;
        doneFlag = (lastDiscrep == 0);
        nxt = 1; // indicates search is not complete yet, more parts remain
    }
    return nxt;
}

/*	----------------------------------------------------------------------------
    ---------- CRC
    ----------------------------------------------------------------------------
 * Arguments:    x
 * Global:       dowcrc - global crc stored here
 * Description:	Update the CRC for transmitted and received data using
                    8-bit CRC equivalent polynomial function : x^8 + x^5 + x + 1
 * 1rst method
        dowcrc = dscrc_table[dowcrc^x];
        return dowcrc;
 * 2nd method
        // from https://www.ccsinfo.com/forum/viewtopic.php?t=37015
        int i = (x ^ dowcrc) & 0xff;
        dowcrc = 0;
        if(i & 1)
        dowcrc ^= 0x5e;
        if(i & 2)
        dowcrc ^= 0xbc;
        if(i & 4)
        dowcrc ^= 0x61;
        if(i & 8)
        dowcrc ^= 0xc2;
        if(i & 0x10)
        dowcrc ^= 0x9d;
        if(i & 0x20)
        dowcrc ^= 0x23;
        if(i & 0x40)
        dowcrc ^= 0x46;
        if(i & 0x80)
        dowcrc ^= 0x8c;
        return dowcrc;
 * 3rd method
        unsigned char r1[16] = {
        0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 
        0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41};
        unsigned char r2[16] = {
        0x00, 0x9d, 0x23, 0xbe, 0x46, 0xdb, 0x65, 0xf8,
        0x8c, 0x11, 0xaf, 0x32, 0xca, 0x57, 0xe9, 0x74};
        int i = (x ^ dowcrc) & 0xff;
        dowcrc = r1[i&0xf] ^ r2[i>>4];
        return dowcrc;
    --------------------------------------------------------------------------*/

Byte DS18B20_crc(Byte x) {
    Byte i = (x ^ dowcrc) & 0xff;

    dowcrc = 0;

    if (i & 1)
        dowcrc ^= 0x5e;
    if (i & 2)
        dowcrc ^= 0xbc;
    if (i & 4)
        dowcrc ^= 0x61;
    if (i & 8)
        dowcrc ^= 0xc2;
    if (i & 0x10)
        dowcrc ^= 0x9d;
    if (i & 0x20)
        dowcrc ^= 0x23;
    if (i & 0x40)
        dowcrc ^= 0x46;
    if (i & 0x80)
        dowcrc ^= 0x8c;

    return dowcrc;
}

/*	----------------------------------------------------------------------------
    ---------- DS18B20StartMeasure()
    ----------------------------------------------------------------------------
 * Description:	reads the ds18x20 device on the 1-wire bus and starting the temperature acquisition
 * Arguments:	pin = pin number where one wire bus is connected.
                    rom = index of the sensor or SKIPROM
                    resolution = 9 to 12 bit resolution
                    t = temperature pointer
    --------------------------------------------------------------------------*/

Byte DS18B20StartMeasure(Byte pin, Byte mem, Byte resolution) {
    Byte res, busy = LOW;
    Byte temp_lsb, temp_msb;
    Int16 temp;

    switch (resolution) {
        case RES12BIT: res = 0b01100000;
            break; // 12-bit resolution
        case RES11BIT: res = 0b01000000;
            break; // 11-bit resolution
        case RES10BIT: res = 0b00100000;
            break; // 10-bit resolution
        case RES9BIT: res = 0b00000000;
            break; //  9-bit resolution
        default: res = 0b00000000;
            break; //  9-bit resolution
            /// NB: The power-up default of these bits is R0 = 1 and R1 = 1 (12-bit resolution)
    }

    if (!DS18B20Configure(pin, mem, 0, 0, res)) return 0; // no alarm

    if (OneWireReset(pin)) return 0;

    if (mem == SKIPROM) {
        // Skip ROM, address all devices
        OneWireWrite(pin, SKIPROM);
    } else {
        // Talk to a particular device
        if (!DS18B20MatchRom(pin, mem)) return 0;
    }

    OneWireWrite(pin, CONVERT_T); // Start temperature conversion
    return 1;
}

/*	----------------------------------------------------------------------------
    ---------- DS18B20ReadMeasure()
    ----------------------------------------------------------------------------
 * Description:	reads the ds18x20 device on the 1-wire bus and returns the temperature previously acquired
 * Arguments:	pin = pin number where one wire bus is connected.
                    rom = index of the sensor or SKIPROM
                    t = temperature pointer
    --------------------------------------------------------------------------*/

Byte DS18B20ReadMeasure(Byte pin, Byte mem, DS18B20_Temperature * t) {
    Byte res, busy = LOW;
    Byte temp_lsb, temp_msb;
    Int16 temp;

    if (OneWireReset(pin)) return 0;

    if (mem == SKIPROM) {
        // Skip ROM, address all devices
        OneWireWrite(pin, SKIPROM);
    } else {
        // Talk to a particular device
        if (!DS18B20MatchRom(pin, mem)) return 0;
    }

    OneWireWrite(pin, READ_SCRATCHPAD); // Read scratchpad

    temp_lsb = OneWireRead(pin); // byte 0 of scratchpad : temperature lsb
    temp_msb = OneWireRead(pin); // byte 1 of scratchpad : temperature msb

    if (OneWireReset(pin)) return 0;

    // Calculation
    // ---------------------------------------------------------------------
    //	Temperature Register Format
    //			BIT7	BIT6	BIT5	BIT4	BIT3	BIT2	BIT1	BIT0
    //	LS BYTE 2^3		2^2		2^1		2^0		2^-1	2^-2	2^-3	2^-4
    //			BIT15	BIT14	BIT13	BIT12	BIT11	BIT10	BIT9	BIT8
    //	MS BYTE S		S		S		S		S		2^6		2^5 	2^4
    //	S = SIGN

    temp = temp_msb;
    temp = (temp << 8) + temp_lsb; // combine msb & lsb into 16 bit variable

    if (temp_msb & 0b11111000) // test if sign is set, i.e. negative
    {
        t->sign = 1;
        temp = (temp ^ 0xFFFF) + 1; // 2's complement conversion
    } else {
        t->sign = 0;
    }

    t->integer = (temp >> 4) & 0x7F; // fractional part is removed, leaving only integer part

    /*	
            t->fraction = 0;					// fractional part
            if (BitRead(temp, 0)) t->fraction +=  625;
            if (BitRead(temp, 1)) t->fraction += 1250;
            if (BitRead(temp, 2)) t->fraction += 2500;
            if (BitRead(temp, 3)) t->fraction += 5000;
     */
    t->fraction = (temp & 0x0F) * 625;
    t->fraction /= 100; // two digits after decimal 

    return 1;
}

#endif	/* DS18B20_H */

