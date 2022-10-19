#include "structs/structs.hpp"
#include "utils/debug.h"
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

    bool redPushed = false, greenPushed = false;

    if (systemState.redButtonPushCount >= 5) {
        redPushed = true;
        systemState.redButtonPushCount = 0;
    }
    if (systemState.greenButtonPushCount >= 5) {
        greenPushed = true;
        systemState.greenButtonPushCount = 0;
    }

    // Swtich from standart to eco mode
    if (greenPushed && !redPushed && systemState.currentMode == 1) {
        systemState.currentMode = 2;
        #ifdef DEBUG
            Serial.println("Switching to eco mode");
        #endif
    } else if (greenPushed && !redPushed && systemState.currentMode == 2) {
        systemState.currentMode = 1;
        #ifdef DEBUG
            Serial.println("Switching to standart mode");
        #endif
    }

    // Switch from standart and eco to maintenance mode
    if (!greenPushed && redPushed && (systemState.currentMode == 1 || systemState.currentMode == 2)) {
        systemState.currentMode = 4;
        #ifdef DEBUG
            Serial.println("Switching to maintenance mode");
        #endif
    } else if (!greenPushed && redPushed && systemState.currentMode == 4) {
        systemState.currentMode = systemState.isEco ? 2 : 1;
        #ifdef DEBUG
            Serial.println("Switching to standart mode");
        #endif
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
        systemState.blinkCounter = (systemState.blinkCounter + 1) % (systemState.blinkMode + 1);
        break;
    }
}
