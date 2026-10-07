#define F_CPU 16000000UL
#include <avr/io.h>
//#include <util/delay.h>

int main(void)
{
    DDRB   = (1 << PB1);                     // PB1 (OC1A) as output: required for the timer to drive it
    OCR1A  = (F_CPU / 256UL / 2UL) - 1;      // 31249: compare match every 0.5 s at 16 MHz
    TCCR1A = (1 << COM1A0);                  // toggle OC1A on each compare match
    TCCR1B = (1 << WGM12) | (1 << CS12);     // CTC mode 4, prescaler 256: this starts the timer

    while (1) {}                             // the CPU has nothing left to do
}