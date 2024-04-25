#include <xc.h>

#define OUTPUT_PIN 0
#define INPUT_PIN 1

/**
 * Sets up pins as input and output
 * Initialize output pins
 */
void setup(void) {
    TRISAbits.TRISA0 = INPUT_PIN;
    TRISAbits.TRISA1 = OUTPUT_PIN;
    TRISAbits.TRISA2 = OUTPUT_PIN;
    TRISAbits.TRISA3 = OUTPUT_PIN;
}