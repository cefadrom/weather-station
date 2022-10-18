#include "config/config.hpp"
#include "components/initComponents.hpp"
#include <Arduino.h>


void initStation() {
    loadConfig();
    initComponents();
}
