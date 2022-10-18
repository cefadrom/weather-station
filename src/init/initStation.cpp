#include "clock/clock.hpp"
#include "components/initComponents.hpp"
#include "config/config.hpp"
#include <Arduino.h>


void initStation() {
    loadConfig();
    initComponents();
    startClock();
}
