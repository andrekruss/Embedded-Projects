/*
 * File:   main.c
 * Author: Andre
 *
 * Created on April 15, 2024, 1:14 PM
 */

#define _XTAL_FREQ 4000000UL

// CONFIG
#pragma config FOSC = INTRCCLK  // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA3/MCLR pin function select (RA3/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include <xc.h>

void main() { 
    
    // TRISA (PORTA TRISTATE REGISTER), RA0 - RA5 available
    // bit 1 = input( tri-stated)
    // bit 0 = output
    TRISA = 0b11111110; // sets RA0 as OUTPUT
    
    PORTAbits.RA0 = 0; // initialize RA0

    while(1) {
        PORTAbits.RA0 = 1; // Set GP1 pin (RB1) high to turn on the LED
        __delay_ms(500);   // Delay for 500 milliseconds
        
        PORTAbits.RA0 = 0; // Set GP1 pin (RB1) low to turn off the LED
        __delay_ms(500);   // Delay for 500 milliseconds
    }
    return;
}