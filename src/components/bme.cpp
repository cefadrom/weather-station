#include "structs/structs.hpp"
#include <Adafruit_BME280.h> //Humidity/Pressure/Temperature
#include <Arduino.h>


#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C


extern Components components;
extern Config config;


// Pressure/Humidity/Temperature measures
void measureBME(SensorMeasures *data) {
    // default settings

    // long measurementStartTime = millis();
    // while ((millis() - measurementStartTime < config.TIMEOUT * 1000) &&
    //        (data->temp == "Na" || data->press == "Na" || data->alt == "Na" ||
    //         data->hum == "Na")) {
    //     if (config.TEMP_AIR)
    //         data->temp = String(components.BME->readTemperature());
    //     if (config.PRESSURE)
    //         data->press = String(components.BME->readPressure() / 100.0F);
    //     data->alt = String(components.BME->readAltitude(SEALEVELPRESSURE_HPA));
    //     if (config.HYGR)
    //         data->hum = String(components.BME->readHumidity());
    // }

    // Code to simulate the BME
    if (config.TEMP_AIR)
        data->temp = String(random(10, 30));
    if (config.PRESSURE)
        data->press = String(random(0, 100));
    data->alt = String(random(0, 100));
    if (config.HYGR)
        data->hum = String(random(0, 100));
}
