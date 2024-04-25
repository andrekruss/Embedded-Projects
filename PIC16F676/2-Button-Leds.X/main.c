/*
 * File:   main.c
 * Author: Andre
 *
 * Created on 17 de Abril de 2024, 10:30
 */

// CONFIG
#pragma config FOSC = INTRCCLK  // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA3/MCLR pin function select (RA3/MCLR pin function is MCLR)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#define _XTAL_FREQ 4000000UL

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define OUTPUT_PIN 0
#define INPUT_PIN 1
#define HIGH 1
#define LOW 0

void main(void) {
    
    ANSELbits.ANS4 = 0;
    ANSELbits.ANS5 = 0;
    ANSELbits.ANS6 = 0;
    ANSELbits.ANS7 = 0;
    
    TRISCbits.TRISC0 = INPUT_PIN;
    TRISCbits.TRISC1 = OUTPUT_PIN;
    TRISCbits.TRISC2 = OUTPUT_PIN;
    TRISCbits.TRISC3 = OUTPUT_PIN;
    
    PORTCbits.RC1 = HIGH;
    PORTCbits.RC2 = LOW; 
    PORTCbits.RC3 = LOW;
    
    int button_counter = 1;
    
    while(true) {
        
        if (PORTCbits.RC0 == HIGH){ 
            
            __delay_ms(250);
            
            button_counter++;
            
            if (button_counter > 3) {
                button_counter = 1;
            }
            
            switch (button_counter) {
                case 1:
                    PORTCbits.RC1 = HIGH;
                    PORTCbits.RC2 = LOW;
                    PORTCbits.RC3 = LOW;
                    break;
                case 2:
                    PORTCbits.RC1 = LOW;
                    PORTCbits.RC2 = HIGH;
                    PORTCbits.RC3 = LOW;
                    break;
                case 3:
                    PORTCbits.RC1 = LOW;
                    PORTCbits.RC2 = LOW;
                    PORTCbits.RC3 = HIGH;
                    break;
                default:
                    PORTCbits.RC1 = LOW;
                    PORTCbits.RC2 = LOW;
                    PORTCbits.RC3 = LOW;
            }
        }        
    }
    
    return;
}
