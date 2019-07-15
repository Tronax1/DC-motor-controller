/* 
 * File:   Helpers.h
 * Author: JORGE VILLAREAL
 *
 * Created on 14 de julio de 2019, 11:06 PM
 */

#ifndef HELPERS_H
#define	HELPERS_H

#define FALSE 0
#define TRUE 1
#define HIGH 1
#define LOW 0

void update(unsigned char data);
void getKey(void);
unsigned char val = 0;
//////////////////////////////////////////////////////////////

void lcd_ini();

void lcdcmd(unsigned char);
void lcddata(unsigned char);
void MSDelay(unsigned int itime);
void writeString(unsigned char sendData[]);

//PWM///////////////////////////
void pwm_init(void);
void pwm_set(int value);
/////////////////////////////////

unsigned char data[] = "Project5";
unsigned int Percentage = 0;
unsigned int Tenths = FALSE;
unsigned int i=0;

#endif	/* HELPERS_H */

