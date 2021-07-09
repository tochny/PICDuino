/* 
 * File:   OneWire.h
 * Author: Alex Chih
 *
 * Created on 2016年7月22日, 下午 3:34
 */

#ifndef ONEWIRE_H
#define	ONEWIRE_H

#include "UniversalLib.h"
#include "ints.h"

static void OneWireLow(Byte);
static void OneWireHigh(Byte);
Byte OneWireReset(Byte);
Byte OneWireReadBit(Byte);
void OneWireWriteBit(Byte, Byte);
Byte OneWireRead(Byte);
void OneWireWrite(Byte, Byte);

#endif	/* ONEWIRE_H */

