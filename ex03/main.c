#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint16_t mod = 10UL;
    DDRB   = (1 << PB1);                         	// PB1 (OC1A) en sortie
    ICR1   = (F_CPU / 256UL) - 1;                 		// 62499 → période de 1 s
    OCR1A = (F_CPU / 256UL * mod / 100UL) - 1;         // mod is at 10% by default
    TCCR1A = (1 << COM1A1) | (1 << WGM11);        // non-inverting : 1 en début de période, 0 au compare match
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12);  // mode 14 + prescaler 256 → démarre

	DDRD &= ~(1 << PD2) | ~(1 << PD4);    // PD2 (SW1) et PD4 (SW2) en entrée → Bouton
    PORTD |= (1 << PD2) | (1 << PD4);    // Activer pull-up sur PD2 et PD4

    while (1) {
		if (!(PIND & (1 << PD2))) {    		// SW1 Bouton pressé (LOW)
            if (mod < 100) mod += 10UL;
			OCR1A = (F_CPU / 256UL * mod / 100UL) - 1;
            _delay_ms(20);                  //debounce
            while (!(PIND & (1 << PD2)));   // Attente du release du bouton
            _delay_ms(20);                  // debounce
        } else if (!(PIND & (1 << PD4))) {    // SW1 Bouton pressé (LOW)
            if (mod > 10) mod -= 10UL;
			OCR1A = (F_CPU / 256UL * mod / 100UL) - 1;
            _delay_ms(20);                 	//debounce
            while (!(PIND & (1 << PD4)));   // Attente du release
            _delay_ms(20);                  //debounce
        }
	}
}