/* 
 * File:   SevenSegament.h
 * Author: Alex Chih
 *
 * Created on 2016年7月25日, 上午 11:46
 */

#ifndef SEVENSEGAMENT_H
#define	SEVENSEGAMENT_H

unsigned SegTable [] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00};

//
//unsigned int num = 0;
//unsigned char cnum[4] = {0, 0, 0, 0};
//unsigned char col = 0;
//if (millis() - time[0] >= 1)
//    {
//        time[0] += 1;
//        int tempnum = num;
//        cnum[0] = tempnum / 1000;
//        tempnum %= 1000;
//        cnum[1] = tempnum / 100;
//        tempnum %= 100;
//        cnum[2] = tempnum / 10;
//        cnum[3] = tempnum % 10;
//        
//        SegData = 0xff;
//        switch (col)
//        {
//        case 0:
//            Com3 = 0;
//            Com2 = 1;
//            Com1 = 1;
//            Com0 = 1;
//            break;
//        case 1:
//            Com3 = 1;
//            Com2 = 0;
//            Com1 = 1;
//            Com0 = 1;
//            break;
//        case 2:
//            Com3 = 1;
//            Com2 = 1;
//            Com1 = 0;
//            Com0 = 1;
//            break;
//        case 3:
//            Com3 = 1;
//            Com2 = 1;
//            Com1 = 1;
//            Com0 = 0;
//            break;
//        }
//        SegData = ~SegTable[cnum[col]];
//        col = col < 3 ? col + 1 : 0;
//    }

#endif	/* SEVENSEGAMENT_H */

