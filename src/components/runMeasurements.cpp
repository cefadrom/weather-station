#include "components/bme.hpp"
#include "components/gps.hpp"
#include "components/light.hpp"
#include "structs/structs.hpp"


Config config;


void runMeasurements(SensorMeasures *data) {
    // Measure the GPS
    measureGPS(data);

    // Measure the BME
    measureBME(data);

    // Measure the light level
    if (config.LUMIN)
        measureLight(data);
}
