#define F_CPU 16000000UL
#include <avr/io.h>
//#include <util/delay.h>

#define CYCLES_PER_ITER 19UL 									//estimation for now
/*
How did we get 19: 

if we dissamssemble the code using avr-objdump -d build/clignotant.bin


a0	ldd r24, Y+1	2	load low byte of i from the stack
a2	ldd r25, Y+2	2	load high byte of i
a4	cpi r24, 0x6A	1	compare i with 0x0A6A (2666)...
a6	sbci r25, 0x0A	1	...including the high byte
a8	brcc .L2		1	not taken while i < 2666
aa	ldd r24, Y+1	2	load i again, because of volatile
ac	ldd r25, Y+2	2	
ae	adiw r24, 1		2	i++
b0	std Y+2, r25	2	store i back to the stack
b2	std Y+1, r24	2	
b4	rjmp .L3		2	jump back
			Total	19



*/

#define ITERS_PER_MS   (F_CPU / 1000UL / CYCLES_PER_ITER)		// 16000000 cycles per seconds, /1000 to get 16000 cycles to waste for a ms. divided by how much our loop cycle consume. 

void my_delay_ms(uint16_t ms)
{
    while (ms--) {
        for (volatile uint16_t i = 0; i < ITERS_PER_MS; i++) {
            // empty; volatile stops the compiler from deleting the loop
        }
    }
}

int main () {
	while (1) {
		my_delay_ms(500);
		PORTB ^= (1 << PB1);
	}
}