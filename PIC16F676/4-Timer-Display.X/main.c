/*
 * File:   main.c
 * Author: Andre
 *
 * Created on 24 de Abril de 2024, 14:49
 */

// CONFIG
#pragma config FOSC = INTRCCLK  // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA3/MCLR pin function select (RA3/MCLR pin function is MCLR)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include <xc.h>

/*
 Fosc = 4MHz
 Fcycle = Fosc / 4 = 1MHz
 prescaler = 4
 Ftimer = Fcycle / prescaler = 250KHz
 Ttimer = 1 / Ftimer = 4us
 Trollover = 255 * 4us = 1,02ms
 if TMR0 = 0x06 => 256-6 = 250 => Trollover = 1ms
 but writting TMR0 inhibits TMR0 for two cycles, 
 so: TMR0 = 0x08
 
 Counting one second: 
 NUM_INTERRUPTS * Trollover = 1s
 NUM_INTERRUPTS = 1s / 1ms = 1000
*/

#define NUMBER_OF_INTERRUPTS 1000
int interrupt_counter = 0;
int display_state = 0;

void change_display_state(void) {
    
    display_state++;
    
    if (display_state > 9) {
        display_state = 0;
    }
    
    switch (display_state) {
        case 0:
            PORTCbits.RC0 = 0;
            PORTCbits.RC1 = 0;
            PORTCbits.RC2 = 0;
            PORTCbits.RC3 = 0;
            break;
        case 1:
            PORTCbits.RC0 = 1;
            PORTCbits.RC1 = 0;
            PORTCbits.RC2 = 0;
            PORTCbits.RC3 = 0;
            break;
        case 2:
            PORTCbits.RC0 = 0;
            PORTCbits.RC1 = 1;
            PORTCbits.RC2 = 0;
            PORTCbits.RC3 = 0;
            break;
        case 3:
            PORTCbits.RC0 = 1;
            PORTCbits.RC1 = 1;
            PORTCbits.RC2 = 0;
            PORTCbits.RC3 = 0;
            break;
        case 4:
            PORTCbits.RC0 = 0;
            PORTCbits.RC1 = 0;
            PORTCbits.RC2 = 1;
            PORTCbits.RC3 = 0;
            break;
        case 5:
            PORTCbits.RC0 = 1;
            PORTCbits.RC1 = 0;
            PORTCbits.RC2 = 1;
            PORTCbits.RC3 = 0;
            break;
        case 6:
            PORTCbits.RC0 = 0;
            PORTCbits.RC1 = 1;
            PORTCbits.RC2 = 1;
            PORTCbits.RC3 = 0;
            break;
        case 7:
            PORTCbits.RC0 = 1;
            PORTCbits.RC1 = 1;
            PORTCbits.RC2 = 1;
            PORTCbits.RC3 = 0;
            break;
        case 8:
            PORTCbits.RC0 = 0;
            PORTCbits.RC1 = 0;
            PORTCbits.RC2 = 0;
            PORTCbits.RC3 = 1;
            break;
        case 9:
            PORTCbits.RC0 = 1;
            PORTCbits.RC1 = 0;
            PORTCbits.RC2 = 0;
            PORTCbits.RC3 = 1;
            break;
        default:
            PORTCbits.RC0 = 0;
            PORTCbits.RC1 = 0;
            PORTCbits.RC2 = 0;
            PORTCbits.RC3 = 0;
    }
}

void __interrupt() isr(void) {
    TMR0 = 0x08;
    INTCONbits.T0IF = 0;
    interrupt_counter++;
    
    if (interrupt_counter >= NUMBER_OF_INTERRUPTS) {
        interrupt_counter = 0;
        change_display_state();
    }
}

void main(void) {
    
    OPTION_REGbits.T0CS = 0; // selects internal cycle clock
    OPTION_REGbits.PSA = 0; // prescaler assigned to TMR0
    OPTION_REGbits.PS = 0b001; // prescaler 1 : 4
    INTCONbits.GIE = 1; // enables all unmasked interrupts
    INTCONbits.T0IE = 1; // enables TMR0 interrupt
    INTCONbits.T0IF = 0; // clears TMR0 overflow interrupt flag
    TMR0 = 0x08; 
    ANSEL = 0x00; // clears ANSEL (sets pins as digital)
    
    // sets RC0, RC1, RC2 and RC3 as OUTPUTS
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;
    
    // initialize display as 0
    PORTCbits.RC0 = 0; 
    PORTCbits.RC1 = 0;
    PORTCbits.RC2 = 0;
    PORTCbits.RC3 = 0;
    
    while(1);
    
    return;
}
