#include "structs/structs.hpp"
#include "utils/led.hpp"
#include "utils/debug.h"
#include "config/config.hpp"
#include <Arduino.h>


extern Components components;
extern SystemState systemState;
extern Config config;


typedef struct Command {
    String key = "";
    String value = "";
    bool keyComplete = false;
} Command;


bool processKeypress(Command *command, char c) {
    Serial.write(c);
    if (c == '\n') {
        return true;
    } else if (c == '=') {
        command->keyComplete = true;
    } else if (command->keyComplete) {
        command->value += c;
    } else {
        command->key += c;
    }
    return false;
}


void processCommand(Command *command) {
    String key = command->key;
    key.trim();
    key.toUpperCase();

    if (key == "RESET") {
        resetConfig();
        Serial.println("Config reset");
    } else if (key == "VERSION") {
        Serial.println("Version: 1");
    } else if (key == "LOG_INTERVAL") {
        if (command->keyComplete) 
            config.LOG_INTERVAL = command->value.toInt();
        Serial.println("Log interval: " + String(config.LOG_INTERVAL) + "s");
    } else if (key == "TIMEOUT") {
        if (command->keyComplete) 
            config.TIMEOUT = command->value.toInt();
        Serial.println("Timeout: " + String(config.TIMEOUT) + "s");
    } else if (key == "MAX_FILE_SIZE") {
        if (command->keyComplete)
            config.MAX_FILE_SIZE = command->value.toInt();
        Serial.println("Max file size: " + String(config.MAX_FILE_SIZE) + " bytes");
    } else {
        Serial.println("Unknown " + String(command->keyComplete ? "set" : "get") + " command " + key);
    }

    // TODO: other commands

    if (command->keyComplete) {
        saveConfig();
    }
}


bool checkIfModeShouldContinue() {
    delay(10);
    return systemState.currentMode == 3;
}


void runConfigMode() {

    #ifndef DEBUG
        Serial.begin(BAUD_RATE);
    #endif
    Serial.println("Starting config mode. Enter config commands");

    // Set the LED to yellow
    setContiniousLed(YELLOW);

    // Main mode loop
    while (checkIfModeShouldContinue()) {
        Command command;
        Serial.print("> ");
        while (checkIfModeShouldContinue()) {
            if (Serial.available() && processKeypress(&command, Serial.read())) {
                processCommand(&command);
                break;
            }
        }
    }

    Serial.println("Exiting config mode");
    #ifndef DEBUG
        Serial.end();
    #endif
}
