/* 
 * File:   UniversalLib.c
 * Author: Alex Chih
 *
 * Created on 2016年7月4日, 下午 2:52
 */

#include "UniversalLib.h"

//<editor-fold defaultstate="collapsed" desc="Interrupts">

void sei()
{
    RCONbits.IPEN = 1;
    INTCONbits.GIEL = 1;
    INTCONbits.GIEH = 1;
    IPR1 = 0b00000000;
    IPR2 = 0b00000010;
}

// <editor-fold defaultstate="collapsed" desc="High Priority Interrupt">

void interrupt HighISR(void) // High Priority Interrupt 
{
#if defined (_TMR1ms_) || defined (_TMR100us_)
    if (TMR0IE && TMR0IF)
    {
        TMR0H = TH;
        TMR0L = TL;
        TMR0IF = 0;
        _time_ = _time_ + 1;
    }
    //    if (TMR3IE && TMR3IF)
    //    {
    //        TMR3H = 251;
    //        TMR3L = 80;
    //        TMR3IF = 0;
    //        PORTD = duty < 1 % 100 ? 0x00 : 0xff;
    //    }
#else 
#define _TMR_NOT_USE_
#warning Timer0 Not Used
#endif
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="Low Priority Interrupt">
char ISRbuffer[64]; //ISR Interrupt Service Routine

void interrupt low_priority LowISR(void) // if data received then goes into here
{
    RCIF = 0;
    if (PIR1bits.RCIF)
    {
        PIR1bits.RCIF = 0;
        for (Int32 i = 0; i < 64; i++)//
            if (ISRbuffer[i] == 0)
            {
                ISRbuffer[i] = ReadUSART();
                if (ISRbuffer[i] == '\r' || ISRbuffer[i] == '\n')
                {
                    RX_DONE = 1;
                    ISRbuffer[i] = 0;
                }
                break;
            }
    }
}
// </editor-fold>

//</editor-fold>


// <editor-fold defaultstate="collapsed" desc="delay">

void delay10us(void)
{
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
}

void delay100us(void)
{
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
}

void delay(unsigned int ms)
{
    unsigned long start = millis();
    while (millis() - start < ms);
}

//void delayMicroseconds(unsigned int us)
//{
//    while(us--);
//}
//</editor-fold>


// <editor-fold defaultstate="collapsed" desc="Timer">
#ifndef _TMR_NOT_USE_

void timer0init(void)
{

    T0CON = 0b10001000;
    TMR0H = TH;
    TMR0L = TL;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    _time_ = 0;
}
#endif

//</editor-fold>


//<editor-fold defaultstate="collapsed" desc="Analog Converter">

void analoginit(void)
{
    //ADCON0 bit 7  6        5   4   3   2              1                   0
    //                        -   -         CHANNEL    GO_DONE     ADON

    ADCON0 = 0b00000001;


    //ADCON1 bit 7  6                        5                                          4  
    //                        -   -    if1,VREF-(AN2)  if0 VSS     if1,VREF+(AN3)  if0 VDD       

    //ADCON1 bit                               5   4   3   2
    //A/D Port Config  Ex: 1011 Set AN3 to AN0 As Analog,  AN12 To AN4 As Digital
    ADCON1 = 0b00001011;



    ADCON2 = 0b10010111;
}

int analogRead(char pin)
{
    int temp;
    TRISA = 0b00001111;
    switch (pin)
    {
    case A0:
        ADCON0 = 0x03;
        break;
    case A1:
        ADCON0 = 0x07;
        break;
    case A2:
        ADCON0 = 0x0B;
        break;
    case A3:
        ADCON0 = 0x0F;
        break;
    }

    ADCON1 = 0b00001011;

    while (ADCON0bits.GO_DONE);
    temp = ADRESH;
    temp <<= 8;
    temp += ADRESL;

    return temp;
}

void analogReference(char Type)
{

    if (Type == DEFAULT) //the default analog reference of 5 volts (on 5V Arduino boards) or 3.3 volts (on 3.3V Arduino boards)
        ADCON1 |= 0x00; //Vref+ = VDD
    else

        if (Type == EXTERNAL) //the voltage applied to the AREF pin (0 to 5V only) is used as the reference.
        ADCON1 |= 0x10; //Vref+ = External source
}

//</editor-fold>


//<editor-fold defaultstate="collapsed" desc="CCP (Capture/Compare/PWM) Module">

//<editor-fold defaultstate="collapsed" desc="Capture">

unsigned long pulseIn(char *PORT, char pin, char state)
{
    int j = 1 << (pin % 8);
    PORT[0x12] |= j;
    T1CON = 0b10110000;
    TMR1H = 0;
    TMR1L = 0;

    while (!state)
        T1CONbits.TMR1ON = 1;
    return -1;
}
//</editor-fold>
//<editor-fold defaultstate="collapsed" desc="PWM">

//void servoinit()
//{
//    TRISD = 0;
//    //Timer1 Registers Prescaler= 1 - TMR1 Preset = 41537 - Freq = 500.02 Hz - Period = 0.002000 seconds
//    T3CON = 0b10000101;
//    TMR3H = 162;
//    TMR3L = 65;
//    TMR3IF = 0;
//    TMR3IE = 1;
//}

double T = 0, Tosc = 0, bestPV = 0;

void SetPWMFrequency(double f)
{
    //// Period Calculation
    // T = (PR2 + 1) * 4 * Tosc * TMRPrescaleValue
    T = 1.0 / f;
    Tosc = 1.0 / _XTAL_FREQ;
    double bestPR = 0;
    bestPV = 0;
    double bestDiff = UInt32_Max;

    for (double prp1 = 1; prp1 <= 256; prp1++)
    {
        double calcT, diff;

        // PV = 1
        calcT = prp1 * 4 * Tosc * 1;
        diff = T - calcT; // f = calcF + diff;
        if (diff < 0) diff = -diff;

        if (diff < bestDiff)
        {
            bestDiff = diff;
            bestPR = prp1 - 1;
            bestPV = 1;
        }

        // PV = 4
        calcT *= 4;
        diff = T - calcT;
        if (diff < 0) diff = -diff;

        if (diff < bestDiff)
        {
            bestDiff = diff;
            bestPR = prp1 - 1;
            bestPV = 4;
        }

        // PV = 16
        calcT *= 4;
        diff = T - calcT;
        if (diff < 0) diff = -diff;

        if (diff < bestDiff)
        {

            bestDiff = diff;
            bestPR = prp1 - 1;
            bestPV = 16;
        }
    }

    PR2 = (Byte) bestPR;
    T2CON = (Byte) (bestPV == 16 ? 2 : bestPV / 4);
    T2CONbits.TMR2ON = 1;
}

void analogWrite(char pin, double dc)
{
    double PW = T * dc / 100;
    double A = PW / (Tosc * bestPV);

    if (pin == PWM0)
    {
        TRISC &= 0b11111011;
        CCPR1L = (Int16) A >> 2;
        CCP1CON = 0b00001100;
        CCP1CON |= ((Byte) A & 0x03) << 4;
    }
    if (pin == PWM1)
    {

        TRISC &= 0b11111101;
        CCPR2L = (Int16) A >> 2;
        CCP2CON = 0b00001100;
        CCP2CON |= ((Byte) A & 0x03) << 4;
    }
}
//</editor-fold>

//</editor-fold>


//<editor-fold defaultstate="collapsed" desc="Pins">

void pinMode(char pin, char mode)
{
    char* port;
    if (pin < 8)
        port = (Byte*) & PORTD;
    else if (pin < 16)
        port = (Byte*) & PORTB;
    else if (pin < 24)
        port = (Byte*) & PORTE;
    else if (pin < 32)
        port = (Byte*) & PORTA;
    else
        port = (Byte*) & PORTC;

    if (mode == INPUT)
        port[0x12] |= 1 << (pin % 8);

    else
        port[0x12] &= ~(1 << (pin % 8));
}

inline void digitalWrite(char pin, char state)
{
    char* port;
    if (pin < 8)
        port = (Byte*) & PORTD;
    else if (pin < 16)
        port = (Byte*) & PORTB;
    else if (pin < 24)
        port = (Byte*) & PORTE;
    else if (pin < 32)
        port = (Byte*) & PORTA;
    else
        port = (Byte*) & PORTC;

    if (state == HIGH)
        port[0] |= 1 << (pin % 8);

    else
        port[0] &= ~(1 << (pin % 8));
}

inline char digitalRead(char pin)
{
    char* port;
    if (pin < 8)
        port = (Byte*) & PORTD;
    else if (pin < 16)
        port = (Byte*) & PORTB;
    else if (pin < 24)
        port = (Byte*) & PORTE;
    else if (pin < 32)
        port = (Byte*) & PORTA;

    else
        port = (Byte*) & PORTC;

    return (port[0] >> (pin % 8)) % 2;
}

//</editor-fold>


//<editor-fold defaultstate="collapsed" desc="wiring_shift">

Byte shiftIn(Byte dataPin, Byte clockPin, Byte bitOrder)
{
    Byte value = 0;
    Byte i;

    for (i = 0; i < 8; ++i)
    {
        digitalWrite(clockPin, HIGH);
        if (bitOrder == LSBFIRST)
            value |= digitalRead(dataPin) << i;
        else
            value |= digitalRead(dataPin) << (7 - i);
        digitalWrite(clockPin, LOW);
    }
    return value;
}

void shiftOut(Byte dataPin, Byte clockPin, Byte bitOrder, Byte val)
{
    Byte i;

    for (i = 0; i < 8; i++)
    {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}


//</editor-fold>


// <editor-fold defaultstate="collapsed" desc="USART">

float Serial_begin(unsigned long baud)
{
    unsigned char BRG_HIGH_OR_LOW = 0;
    if (baud > 19200)
        BRG_HIGH_OR_LOW = 16; //BRG_HIGH_SPEED
    else
        BRG_HIGH_OR_LOW = 64; //BRG_LOW_SPEED

    unsigned char rate = _XTAL_FREQ / baud / BRG_HIGH_OR_LOW - 1;

    for (Int32 i = 0; i < 64; i++)
        ISRbuffer[i] = 0;
    OpenUSART(USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & (BRG_HIGH_OR_LOW == 64 ? USART_BRGH_LOW : USART_BRGH_HIGH), rate);
    RCIF = 0;
    return (((_XTAL_FREQ / (64.0 * (rate + 1))) - baud) / baud) * 100.0; // error rate
}

void Serial_print(String string)
{
    while (string[0])
    {

        while (BusyUSART());
        WriteUSART(string[0]);
        string++;
    }
}

void Serial_println(String string)
{
    Serial_print(string);

    while (BusyUSART());
    WriteUSART(0x0A);
}

void Serial_write(char byte)
{

    while (BusyUSART());
    WriteUSART(byte);
}

String Serial_read()
{
    char buffer[65];
    buffer[64] = 0x00; // make sure it is fine
    for (Int32 i = 0; i < 64; i++)
    {

        buffer[i] = ISRbuffer[i];
        ISRbuffer[i] = 0;
    }
    RX_DONE = 0;
    return buffer;
}

//</editor-fold>


//<editor-fold defaultstate="collapsed" desc="math method">

double map(double x, double i_min, double i_max, double o_min, double o_max)
{
    return (x - i_min) * (o_max - o_min) / (i_max - i_min) + o_min;
}

//</editor-fold>


//<editor-fold defaultstate="collapsed" desc="Taylormade functions">
void PutNumber(char container[16][16], char data[5][7], int offsetX, int offsetY)
{
    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 7; y++)
            if (offsetX + x >= 0 && offsetX + x < 16 && offsetY + y >= 0 && offsetY + y < 16)
                container[offsetX + x][offsetY + y] = data[x][y];
}

//</editor-fold>


//<editor-fold defaultstate="collapsed" desc="Int And String Converter">

String Int32ToString(Int32 val)
{
    // Bits
    char num[15];

    // Clear??
    for (Int32 i = 0; i < 15; i++)
        num[i] = 0;

    if (val == 0)
    {
        num[0] = '0';
        num[1] = 0;
        return num;
    }

    // Check if val is negative
    if (val < 0)
    {
        num[0] = '-';
        val = -val;
    }

    // Split val(long) into num(char[])
    Int32 offset = num[0] == '-' ? 1 : 0;

    while (val != 0)
    {
        num[offset] = 48 + (val % 10);
        offset++;
        val /= 10;
    }

    // Find last valid bit
    Int32 lastIndex = offset - 1;

    // Reverse array
    for (Int32 i = 0; i <= lastIndex / 2; i++)
    {

        Int32 temp = num[i];
        num[i] = num[lastIndex - i];
        num[lastIndex - i] = temp;
    }

    /*Done*/
    return num;
}

Int32 StringToInt32(String val)
{
    // find end index
    Int32 end = 0;
    while (val[end] != 0)
        end++;

    // calculate
    Int32 sum = 0;

    for (Int32 i = end - 1, add = 1; i >= 0; i--, add *= 10)
        sum += add * (val[i] - 0x30);

    /* Done */
    return sum;
}

String Int16ToString(Int16 val)
{
    // Bits
    char num[7];

    // Clear??
    for (Int32 i = 0; i < 7; i++)
        num[i] = 0;

    // Check if val is negative
    if (val < 0)
    {
        num[0] = '-';
        val = -val;
    }


    // Split val(long) into num(char[])
    Int32 offset = num[0] == '-' ? 1 : 0;
    while (val != 0)
    {
        num[offset] = 48 + (val % 10);
        offset++;

        val /= 10;
    }

    // Find last valid bit
    Int32 lastIndex = offset - 1;

    // Reverse array
    for (Int32 i = 0; i < lastIndex / 2; i++)
    {

        Int32 temp = num[i];
        num[i] = num[lastIndex - i];
        num[lastIndex - i] = temp; // fuck that
    }

    /*Done*/
    return num;
}

String ByteToString(Byte val)
{
    // Bits
    char num[5];

    // Clear??
    for (Int32 i = 0; i < 5; i++)
        num[i] = 0;


    // Split val(long) into num(char[])
    Int32 offset = 0;
    while (val != 0)
    {
        num[offset] = 48 + (val % 10);
        offset++;

        val /= 10;
    }

    // Find last valid bit
    int lastIndex = offset - 1;

    // Reverse array
    for (Int32 i = 0; i < lastIndex / 2; i++)
    {

        Int32 temp = num[i];
        num[i] = num[lastIndex - i];
        num[lastIndex - i] = temp; // fuck that
    }

    /*Done*/
    return num;
}

//</editor-fold>


//<editor-fold defaultstate="collapsed" desc="String : Max length = 255">

String String_Add(String l, String r)
{
    char string[64];

    Int32 offset = 0;
    // Add left string l(String)
    for (Int32 i = 0; l[i] != 0; i++, offset++)
        string[offset] = l[i];

    // Add right string r(String)

    for (Int32 i = 0; r[i] != 0; i++, offset++)
        string[offset] = r[i];

    // End string
    string[offset] = 0;

    /*Done*/
    return string;
}

String String_Substring(String target, Int32 startIndex, Int32 length)
{
    char string[64];

    Int32 offset;

    for (offset = 0; offset < length; offset++)
        string[offset] = target[offset + startIndex];
    string[offset] = 0;

    return string;
}

String String_Left(String target, Int32 length)
{
    char string[64];

    Int32 offset;
    for (offset = 0; offset < length; offset++)
        string[offset] = target[offset];
    string[offset] = 0;

    return string;
}
//</editor-fold>