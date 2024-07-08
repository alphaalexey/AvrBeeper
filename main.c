#include <avr/io.h>
#include <util/delay.h>

const int delays[] = {
    200, 200, 200, 200, 100, 200, 200, 100, 300,
    200, 200, 200, 200, 100, 200, 200, 100, 300, 0
};

const int tones[] = {
    3, 3, 3, 1, 5, 3, 1, 5, 3,
    7, 7, 7, 8, 5, 3, 1, 5, 3, 0
};

void delay_us(unsigned int us) {
    for (unsigned int i = 0; i < us; i++) {
        __builtin_avr_delay_cycles(F_CPU / 1000000UL);
    }
}

void beep(int tone) {
    /* make beep sound */
    for (int i = 0; i < 100 * tone; i++) {
        PORTB |= _BV(PB0); // Sound ON
        delay_us(1000 / tone);

        PORTB &= ~_BV(PB0); // Sound OFF
        delay_us(1000 / tone);
    }
}

int main(void) {
    DDRB |= _BV(DDB0); // MAKE PORT B0 PIN OUTPUT

    register const int *delay = &delays[0];
    register const int *tone = &tones[0];
    while (*delay && *tone) {
        beep(*(tone++));

        for (int i = 0; i < *delay; i++) _delay_ms(1);
        delay++;
    }
}
