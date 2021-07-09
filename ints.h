/* 
 * File:   ints.h
 * Author: Alex Chih
 *
 * Created on 2016年7月28日, 下午 2:57
 */

#ifndef INTS_H
#define	INTS_H

typedef signed char SByte;
#define SByte SByte
#define INT8_MIN (-128)
#define INT8_MAX (127)
typedef unsigned char Byte;
#define Byte Byte
#define Byte_Min (0)
#define Byte_Max (255)

typedef unsigned int UInt16;
#define UInt16 UInt16
#define UInt16_Min (0)
#define UInt16_Max (65535U)
typedef signed int Int16;
#define Int16 Int16
#define INT16_MIN (-32768)
#define INT16_MAX (32767)

typedef unsigned short long int UInt24;
#define UInt24 UInt24
#define UInt24_Min (0)
#define UInt24_Max (16777215UL)
typedef signed short long int Int24;
#define Int24 Int24
#define Int24_Min (-8388608L)
#define Int24_Max (8388607L)

typedef unsigned long int UInt32;
#define UInt32 UInt32
#define UInt32_Min (0)
#define UInt32_Max (4294967295UL)
typedef signed long int Int32;
#define Int32 Int32 // Int32
#define Int32_Min (-2147483648L)
#define Int32_Max (2147483647L)


#endif
