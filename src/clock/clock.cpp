#include "structs/structs.hpp"
#include <Arduino.h>


extern Config config;
extern Components components;
extern SystemState systemState;


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
    // Buttons
    if (digitalRead(RED_BUTTON_PIN) == LOW) {
        systemState.redButtonPushCount++;
    } else {
        systemState.redButtonPushCount = 0;
    }

    if (digitalRead(GREEN_BUTTON_PIN) == LOW) {
        systemState.greenButtonPushCount++;
    } else {
        systemState.greenButtonPushCount = 0;
    }

    if (systemState.redButtonPushCount >= 5) {
        Serial.println("red button pushed");
        systemState.redButtonPushCount = 0;
    }
    if (systemState.greenButtonPushCount >= 5) {
        Serial.println("green button pushed");
        systemState.greenButtonPushCount = 0;
    }

    // LEDs
    switch (systemState.blinkMode) {
    case 0:
        components.leds->setColorRGB(0, systemState.ledColor1[0],
                                     systemState.ledColor1[1],
                                     systemState.ledColor1[2]);
        break;

    case 1:
    case 2:
        if (systemState.blinkCounter == 0) {
            components.leds->setColorRGB(0, systemState.ledColor1[0],
                                         systemState.ledColor1[1],
                                         systemState.ledColor1[2]);
        } else {
            components.leds->setColorRGB(0, systemState.ledColor2[0],
                                         systemState.ledColor2[1],
                                         systemState.ledColor2[2]);
        }
        // Increment the counter and reset it if it's too high
        systemState.blinkCounter =
            (systemState.blinkCounter + 1) % (systemState.blinkMode + 1);
        break;
    }
}
