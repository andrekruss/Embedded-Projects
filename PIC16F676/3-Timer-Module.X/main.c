/*
 * File:   main.c
 * Author: Andre
 *
 * Created on 21 de Abril de 2024, 14:04
 */

#include <xc.h>

// CONFIG
#pragma config FOSC = INTRCCLK  // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA3/MCLR pin function select (RA3/MCLR pin function is MCLR)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

// INT_NUMBER = DESIRED_TIME / ROLLOVER_TIME
#define INTERRUPTS_NUMBER 30 // 30 interrupts ~= 1.965s
int interrupt_counter = 0; 

void change_led_status() {
    if (interrupt_counter >= INTERRUPTS_NUMBER) {
        PORTCbits.RC0 = !PORTCbits.RC0;
        interrupt_counter = 0;
    }
}

void __interrupt() isr(void) {
    TMR0 = 0x00;
    INTCONbits.T0IF = 0;
    interrupt_counter++;
    change_led_status();
}

void main(void) {
    
    OPTION_REGbits.T0CS = 0; // clock source = internal
    OPTION_REGbits.PSA = 0; // sets prescaler to WDT (so TMR0 rate will be 1:1)
    OPTION_REGbits.PS = 0b111; // prescaler 1:256, for slowing Fcycle by 256 (OBS: Fcycle = Fosc / 4)
    // so Ftimer = Fosc / (4 * 256) ~= 3906Hz
    // Ttimer = 1 / Ftimer ~= 0,256ms
    // Timer Rollover = 256 * 0,256ms ~= 65.5ms
    
    INTCONbits.GIE = 1;
    INTCONbits.T0IE = 1; // enables TMR0 interrupt
    INTCONbits.T0IF = 0; 
    
    ANSEL = 0x00;
    
    TRISCbits.TRISC0 = 0;
   
    PORTCbits.RC0 = 0;
    
    TMR0 = 0x00; // initializing timer counter to 0
    
    while(1){
        
    }
}