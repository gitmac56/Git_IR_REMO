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

static short Capture[100];
static int NCapture = 0;

CY_ISR(do_capture) {
    Timer1_STATUS;
    Capture[NCapture++] = Timer1_ReadCapture();
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
        while ((Timer2_ReadStatusRegister() & Timer2_STATUS_TC) == 0);
        NCapture=0;
        Timer1_ClearFIFO();
        Timer1_Init();
        Timer1_Enable();
        Timer1_WriteCounter(25000);
        Timer1_WritePeriod(25000);
        while (IR_Read() != 0);
        ISR1_Enable();
        LED_Write(1);
        while (Timer1_ReadCounter() > 10);
        ISR1_Disable();
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
        }
        if (NCapture <= 2) {
            rep = 1;
        }
        else {
            rep = 0;
            code = -1;
        }
        

        if (NCapture >=34) {
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
        snprintf(buf, 80, "%x, %x\r\n", code, L);
        Puts(buf);
    }
}
