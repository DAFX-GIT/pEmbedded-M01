#include <avr/io.h>
//#include <util/delay.h>

int main(void)
{
    DDRB   = (1 << PB1);                          // PB1 (OC1A) en sortie
    ICR1   = (F_CPU / 256UL) - 1;                 // 62499 → période de 1 s
    OCR1A  = (F_CPU / 256UL / 10UL) - 1;          // 6249  → allumée 0,1 s (10 %)
    TCCR1A = (1 << COM1A1) | (1 << WGM11);        // non-inverting : 1 en début de période, 0 au compare match
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12);  // mode 14 + prescaler 256 → démarre

    while (1) {}
}