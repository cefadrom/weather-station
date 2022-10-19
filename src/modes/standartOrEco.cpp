#include "structs/structs.hpp"
#include "utils/led.hpp"
#include "utils/wait.hpp"
#include "utils/debug.h"
#include <Arduino.h>


extern Config config;
extern Components components;
extern SystemState systemState;


bool checkIfModeShouldContinue(bool isEco) {
    // Weird workaround to not skip the execution
    delay(10);
    return (isEco && systemState.currentMode == 2) ||
           (!isEco && systemState.currentMode == 1);
}


void runStandartOrEcoMode(bool isEco) {

    #ifdef DEBUG
        Serial.println("Starting " + String(isEco ? "eco" : "standart") + " mode");
    #endif

    // Set the LED
    if (isEco)
        setContiniousLed(RED);
    else
        setContiniousLed(GREEN);

    systemState.isEco = isEco;

    unsigned int waitDelay = isEco ? config.LOG_INTERVAL * 2 : config.LOG_INTERVAL;

    // Main mode loop
    while (checkIfModeShouldContinue(isEco)) {
        // TODO: measures
        wait(waitDelay, []() { return checkIfModeShouldContinue(true); });
        Serial.println("TODO: Get measures");
    }


    #ifdef DEBUG
        Serial.println(String(isEco ? "Eco" : "Standart") + " mode is done");
    #endif
}
