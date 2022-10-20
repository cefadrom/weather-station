#include "structs/structs.hpp"
#include <Arduino.h>
#include <MicroNMEA.h>


extern Components components;
extern Config config;


void measureGPS(SensorMeasures *data) {
    // unsigned char buffer[96];
    // MicroNMEA nmea(buffer, sizeof(buffer));
    // components.GPS->begin(9600);

    // long measurementStartTime = millis();
    // while (millis() - measurementStartTime < (config.TIMEOUT * 1000)) {
    //     if (!components.GPS->available() ||
    //         !nmea.process(components.GPS->read()) || !nmea.isValid())
    //         continue;
    //     data->GPS.latitude = nmea.getLatitude();
    //     data->GPS.longitude = nmea.getLongitude();
    //     break;
    // }

    // components.GPS->end();

    // Code to simulate the GPS and an error 1/8 times
    if (random(0, 8) == 2)
        return;
    data->GPS.latitude = String(random(48000, 49000));
    data->GPS.longitude = String(random(6000, 7000));
}
