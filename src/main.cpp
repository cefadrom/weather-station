#include "init/initStation.hpp"
#include "modes/configuration.hpp"
#include "modes/maintenance.hpp"
#include "modes/standartOrEco.hpp"
#include "structs/structs.hpp"
#include "utils/debug.h"


Config config;
Components components;
SystemState systemState;


void setup() {
    // Initialize the station
    initStation();

    // Init done, start the mode
    if (digitalRead(RED_BUTTON_PIN) == LOW)
        systemState.currentMode = 3;
    else
        systemState.currentMode = 1;

    #ifdef DEBUG
        Serial.begin(BAUD_RATE);
    #endif
}


void loop() {
    switch (systemState.currentMode) {
        {
        case 1: runStandartOrEcoMode(false); break;

        case 2: runStandartOrEcoMode(true); break;

        case 3: runConfigMode(); break;

        case 4: runMaintenanceMode(); break;
        }
    }

    #ifdef DEBUG
        Serial.println("Switching mode");
    #endif
}
