#include "systick.h"

void systick_begin(void) {
    // set
    bitClear(TCCR2B, WGM22);
    bitClear(TCCR2A, WGM20);
    bitSet(TCCR2A, WGM21);
    // set divisor to 128 => 125kHz
    bitSet(TCCR2B, CS22);
    bitClear(TCCR2B, CS21);
    bitSet(TCCR2B, CS20);
    OCR2A = 249; // (16000000/128/500)-1 => 500Hz
    bitSet(TIMSK2, OCIE2A);
    delay(40); // make sure it runs for a few cycles before we continue
}

void systick_update(void) {
}
