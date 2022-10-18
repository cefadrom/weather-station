#include "structs/structs.hpp"
#include <Arduino.h>


extern Config config;
extern Components components;


void startClock() {
    // Set the clock to 1 Hz
    // https://passionelectronique.fr/introduction-timer-arduino#exemple-de-code-2-faire-clignoter-une-led-a-1-hz-en-utilisant-les-interruptions
    noInterrupts();
    bitClear(TCCR1A, WGM10);
    bitClear(TCCR1A, WGM11);
    bitSet(TCCR1B, WGM12);
    bitClear(TCCR1B, WGM13);
    bitClear(TCCR1B, CS10);
    bitClear(TCCR1B, CS11);
    bitSet(TCCR1B, CS12);
    bitSet(TIMSK1, OCIE1A);
    TCNT1 = 0;
    OCR1A = 62500; // Clock period, 62500 is for 1 Hz
    interrupts();
}


ISR(TIMER1_COMPA_vect) {
    // Blibk the LED
    static bool ledState = false;
    if (ledState)
        components.leds->setColorRGB(0, 255, 0, 0);
    else
        components.leds->setColorRGB(0, 0, 0, 255);
    ledState = !ledState;
}
