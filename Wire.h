/* 
 * File:   Wire.h
 * Author: Alex Chih
 *
 * Created on 2016年7月19日, 下午 4:38
 */

#ifndef WIRE_H
#define	WIRE_H
#include "ints.h"
#include "UniversalLib.h"
#include <plib\i2c.h>

void Wire_begin();
void Wire_beginTransmission(Byte address);
void Wire_endTransmission();
void Wire_write(Byte);
Byte Wire_read(Byte, Byte); //incomplete

#endif	/* WIRE_H */

