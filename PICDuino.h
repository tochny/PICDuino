/* 
 * File:   PICDuino.h
 * Author: Alex Chih
 *
 * Created on 2016年8月3日, 下午 1:28
 */

#ifndef PICDUINO_H
#define	PICDUINO_H

#include "UniversalLib.h"
#include "start.h"

void init() 
{
    sei();

    timer0init();
    analoginit();
    SetPWMFrequency(25000);
}

int main()
{
    init();
    Setup();
    
    for(;;)
        Loop();
    
    return 0;
}


#endif	/* PICDUINO_H */

