#include "structs/structs.hpp"
#include "utils/led.hpp"
#include "utils/wait.hpp"
#include "utils/debug.h"
#include "components/runMeasurements.hpp"
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
        SensorMeasures data;
        runMeasurements(&data);
        Serial.println("----- MEASUREMENTS -----");
        Serial.println("Temperature: " + data.temp);
        Serial.println("Pressure: " + data.press);
        Serial.println("Altitude: " + data.alt);
        Serial.println("Humidity: " + data.hum);
        Serial.println("Latitude: " + data.GPS.latitude);
        Serial.println("Longitude: " + data.GPS.longitude);
        Serial.println("Light level: " + data.lightlevel);
        wait(2, []() { return systemState.currentMode == 4; });
    }

    Serial.println("Exiting maintenance mode");
    #ifndef DEBUG
        Serial.end();
    #endif
}
