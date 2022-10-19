#include "structs/structs.hpp"
#include "utils/led.hpp"
#include "utils/debug.h"
#include <Arduino.h>


extern Components components;
extern SystemState systemState;


void runConfigMode() {

    #ifndef DEBUG
        Serial.begin(BAUD_RATE);
    #endif
    Serial.println("Starting config mode. Enter config commands");

    // Set the LED to yellow
    setContiniousLed(YELLOW);

    // Main mode loop
    while (systemState.currentMode == 3) {
        while (Serial.available())
            Serial.write(Serial.read());
    }

    Serial.println("Exiting config mode");
    #ifndef DEBUG
        Serial.end();
    #endif
}
