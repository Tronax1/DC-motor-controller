void pwm_init(){
    CCP1CON = 0;    //clear CCP1CON
    PR2 = 124;      //[8MHz/(4 * 1KHz * 16)] - 1 = 124   Pre-scalar = 16.
    CCPR1L = 31;    //Initialize to 10%
    T2CON = 0x02;   //Timer2, 16 Pre-scale, no post-scalar
    CCP1CON = 0x0C; //PWM mode, 00 for DC1B1:B0
    TMR2 = 0;       //clear Timer2
    T2CONbits.TMR2ON = 1; //Turn on Timer2
}

void pwm_set(char value[]){
    int val = atoi(value);          //turn input into integer
    float val2 = (float)val/100;    //turn integer into percentage (50 -> .5)
    CCPR1L = 124 * val2;
}