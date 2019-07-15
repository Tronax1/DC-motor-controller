#include "Helpers.h"
#include <pic18f45k50.h>
#include <xc.h>
#define _XTAL_FREQ 8000000

#define rs PORTCbits.RC0
#define rw PORTCbits.RC1
#define en PORTDbits.RD3
//LCD Data pins
#define lcdport PORTA

//4x4 Matrix stuff/////////////////////////////////////////
#define R1 PORTBbits.RB0
#define R2 PORTBbits.RB1
#define R3 PORTBbits.RB2
#define R4 PORTBbits.RB3
#define C1 PORTBbits.RB4
#define C2 PORTBbits.RB5
#define C3 PORTBbits.RB6
#define C4 PORTBbits.RB7

#define PWMPort PORTCbits.RC2

void writeString(unsigned char sendData[])
{
    unsigned int i = 0;
    while(sendData[i]!='\0')
    {
        lcddata(sendData[i]); // Call lcddata function to send characters
        // one by one from "data" array
        i++;
        __delay_ms(2);
    }
}

void lcd_ini(){
    lcdcmd(0x38); // Configure the LCD in 8-bit mode, 2 line and 5x7 font
    lcdcmd(0x0C); // Display On and Cursor Off
    lcdcmd(0x01); // Clear display screen
    lcdcmd(0x06); // Increment cursor
    lcdcmd(0x80); // Set cursor position to 1st line, 1st column
}

void lcdcmd(unsigned char cmdout){
    lcdport=cmdout; //Send command to lcdport=PORTA
    rs=0;
    rw=0;
    en=1;
    __delay_ms(10);
    en=0;
}
void lcddata(unsigned char dataout){
    lcdport=dataout; //Send data to lcdport=PORTA
    rs=1;
    rw=0;
    en=1;
    __delay_ms(10);
    en=0;
}

void getKey(){
    while(val =='n')
    {
        LATB = 0xf0;
        if(C1 == LOW){
            R1 = HIGH;
            if(C1 == HIGH)
             update('1');     
            else {
                R1 = LOW;
                R2 = HIGH;
                if(C1 == HIGH)
                    update('4');
                else {
                    R2 = LOW;
                    R3 = HIGH;
                    if(C1 == HIGH)
                        update('7');
                    else {
                        R3 = LOW;
                        R4 = HIGH;
                        if(C1 == HIGH){
                            
                            update('*');
                        }
                            
                    }
                }
            }
        }
        //LATB = 0xf0;
        else if(C2 == LOW){
            R4 = LOW;
            R1 = HIGH;
                if(C2 == HIGH)
                    update('2');
                else {
                    R1 = LOW;
                    R2 = HIGH;
                    if(C2 == HIGH)
                        update('5');
                    else{
                        R2 = LOW;
                        R3 = HIGH;
                        if(C2 == HIGH)
                            update('8');
                        else {
                            R3 = LOW;
                            R4 = HIGH;
                            if(C2 == HIGH)
                                update('0');
                        }
                    }
                }
        }
        //LATB = 0xf0;
        else if(C3 == LOW){
            R4 = LOW;    
            R1 = HIGH;
                if(C3 == HIGH)
                    update('3');
                else {
                    R1 = LOW;
                    R2 = HIGH;
                    if(C3 == HIGH)
                        update('6');
                    else{
                        R2 = LOW;
                        R3 = HIGH;
                        if(C3 == HIGH)
                            update('9');
                        else {
                            R3 = LOW;
                            R4 = HIGH;
                            if(C3 == HIGH){
                            pwm_set(Percentage);
                            Percentage = 0;
                            //update('#');
                            }
                                
                        }
                    }
                }
        }
        //LATB = 0xf0;
         if(C4 == HIGH){
            R4 = LOW;    
            R1 = HIGH;
                if(C4 == LOW)
                    update('D');
                else {
                    R1 = LOW;
                    R2 = HIGH;
                    if(C4 == LOW)
                        update('A');
                    else{
                    R2 = LOW;    
                    R3 = HIGH;
                        if(C4 == LOW)
                            update('B');
                        else {
                            R3 = LOW;
                            R4 = HIGH;
                            if(C4 == LOW)
                                update('C');
                        }    
                    }   
                }
        }
        if(val!='n')
            lcddata(val);
        __delay_ms(300);
    }   // end of while(1)
}

void update(unsigned char data)
{
    val = data;
    Percentage = (data - '0')*10;
}



void pwm_init(){
    CCP1CON = 0;    //clear CCP1CON
    PR2 = 124;      //[8MHz/(4 * 1KHz * 16)] - 1 = 124   Pre-scalar = 16.
    CCPR1L = 0;    //Initialize to 10%
    TRISCbits.TRISC2 = 0;
    T2CON = 0x02;   //Timer2, 16 Pre-scale, no post-scalar
    CCP1CON = 0x3C; //PWM mode, 00 for DC1B1:B0
    TMR2 = 0;       //clear Timer2
    T2CONbits.TMR2ON = 1; //Turn on Timer2
}

void pwm_set(int value){
    float val2 = (float)value/100;    //turn integer into percentage (50 -> .5)
    CCPR1L = 124 * val2;
}