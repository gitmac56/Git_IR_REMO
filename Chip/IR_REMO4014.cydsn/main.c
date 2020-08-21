/* ========================================
 *
 * Copyright AGRI-HITECH LLC, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 * ========================================
 * Program & Coded by fanfan (mac@line.to)
*/
#include "project.h"
#include <stdio.h>

#define T1Period 26000
#define CodeL 34

enum { FR = 1, FL = 2, BR = 4, BL = 8} M_Stat;

const struct KEY {
    short code; char motor; } key[] = {
        {0x10b1,(FL)},
        {0x10a0,(FR|FL)},
        {0x1021,(FR)},
        {0x1010,(FL|BR)},
        {0x1020,0},
        {0x1080,(BL|FR)},
        {0x1011,(BL)},
        {0x1000,(BL|BR)},
        {0x1081,(BR)},
        {0,0}
    };
static short Capture[100];
static int NCapture = 0;

CY_ISR(do_capture) {
    Timer1_STATUS;
    Capture[NCapture++] = Timer1_ReadCapture();
}

CY_ISR(do_stop) {
    Timer2_STATUS;
    M_BL_Write(0);
    M_BR_Write(0);
    M_FL_Write(0);
    M_FR_Write(0);
}

void Puts(const char *s) {
    UART1_UartPutString(s);
}

int main(void)
{
    char buf[80];
    unsigned rep, code = 0;
    unsigned char b0, b1, b2, b3;
    
    int i;

    UART1_Start();
    Timer1_Start();
    Timer2_Start();
    
    ISR1_StartEx(do_capture);
    CyGlobalIntEnable;
    
    for(;;)
    {  
        ISR1_Disable();
        ISR1_ClearPending();
        Timer2_WriteCounter(255);
        while (Timer2_ReadCounter() > (255-8));
        NCapture=0;
        Timer1_ClearFIFO();
        Timer1_Init();
        Timer1_Enable();
        Timer1_WriteCounter(T1Period);
        Timer1_WritePeriod(T1Period);        
        LED_Write(1);
        ISR1_Enable();
        
        while (Timer1_ReadCounter() > 10);
        LED_Write(0);
        snprintf(buf, 80, "interrupt %d\r\n", NCapture);
        Puts(buf);
        unsigned L = 0;
        for (i = 1; i < NCapture; i++) {
            unsigned long bit;
            int diff;
            
            diff = Capture[i-1] -Capture[i];
 
            if (diff < 450) {
                bit = 0;
            }
            else {
                bit = 0x80000000u;
            }
            L >>= 1;
            L = L | bit;
            if (i >= CodeL) break;
        }
        if (NCapture <= 3) {
            rep = 1;
        }
        else {
            rep = 0;
            code = -1;
        }
        

        if (NCapture >= CodeL) {
            b0 = L & 0xff;
            b1 = (L & 0xff00) >> 8;
            b2 = (L & 0xff0000) >> 16;
            b3 = (L & 0xff000000) >> 24;
            if (((b0 ^ (~b1 & 0xff)) | (b2 ^ (~b3 & 0xff))) == 0) {
                code = ((b0 & 0xff) << 8) | (b2 & 0xff);
            }
            else if (rep == 0) {
                code = -1;
            }
        }      
        snprintf(buf, 80, "%x\r\n", L);
        Puts(buf);
        
        struct KEY const *p;
        for (p = &key[0]; p->code != 0; p++) {
            if ((short)code == p->code) {
                if (p->motor & BL) {
                    M_BL_Write(1); Puts("BL ");
                };
                if (p->motor & BR) {
                    M_BR_Write(1); Puts("BR ");
                };
                if (p->motor & FL) {
                    M_FL_Write(1); Puts("FL ");
                };
                if (p->motor & FR) {
                    M_FR_Write(1); Puts("FR ");
                };
                Puts("\r\n");
                break;
            }
        }
        
    }
}
