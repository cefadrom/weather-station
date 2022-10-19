#include "structs/structs.hpp"
#include "utils/led.hpp"
#include "utils/wait.hpp"
#include "utils/debug.h"
#include <Arduino.h>


extern Components components;
extern SystemState systemState;


void runMaintenanceMode() {

    // Set the LED to orange
    setContiniousLed(ORANGE);

    #ifndef DEBUG
        Serial.begin(BAUD_RATE);
    #endif
    Serial.println("Starting maintenance mode");

    // Main mode loop
    while (systemState.currentMode == 4) {
        Serial.println("TODO: Get measures");
        wait(2, []() { return systemState.currentMode == 4; });
    }

    Serial.println("Exiting maintenance mode");
    #ifndef DEBUG
        Serial.end();
    #endif
}
