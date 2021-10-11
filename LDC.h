/* 
 * File:   LDC.h
 * Author: Felipe
 *
 * Created on 10 de octubre de 2021, 07:29 PM
 */

#include <stdio.h>
#include <xc.h>
#include <pic18f4550.h>
#include "config.h"
#include <stdlib.h>
#include <ctype.h>

#ifndef LDC_H
#define	LDC_H

#ifdef	__cplusplus
extern "C" {
#endif


#define input 1;
#define ouput 0;
#define on 0;
#define off 0;
#define conf_RS TRISDbits.TRISD0;
#define conf_EN TRISDbits.TRISD1;
#define conf_D4 TRISDbits.TRISD4;
#define conf_D5 TRISDbits.TRISD5;
#define conf_D6 TRISDbits.TRISD6;
#define conf_D7 TRISDbits.TRISD7;
#define RS RD0;
#define EN RD1;
#define D4 RD0;
#define D5 RD5;
#define D6 RD6;
#define D7 RD7;
    void Estado_Sis(int count);
    void Lcd_Port(char a);
    void Lcd_Cmd(char a);
    void Lcd_Clear(void);
    void Lcd_Set_Cursor(char a, char b);
    void Lcd_Init(void);
    void Lcd_Write_Char(char a);
    void Lcd_Write_String(char *a);
    void delay_ms(unsigned int delay_val);


#ifdef	__cplusplus
}
#endif

#endif	/* LDC_H */

