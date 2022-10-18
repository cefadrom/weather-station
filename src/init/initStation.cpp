#include "config/config.hpp"
#include "sensors/initSensors.hpp"
#include <Arduino.h>


void initStation() {
    loadConfig();
    initSensors();
}
