#include "structs/structs.hpp"


extern Components components;
extern Config config;


void measureLight(SensorMeasures *data) {
    if (!config.LUMIN)
        return;

    long measurementStartTime = millis();
    while (millis() - measurementStartTime < (config.TIMEOUT * 1000) &&
           data->lightlevel == "Na") {
        unsigned short lightValue = analogRead(LIGHT_SENSOR_PIN);
        if (lightValue <= config.LUMIN_LOW) {
            lightValue = config.LUMIN_LOW;
        }
        if (lightValue >= config.LUMIN_HIGH) {
            lightValue = config.LUMIN_HIGH;
        }
        data->lightlevel = String(lightValue);
    }
}
