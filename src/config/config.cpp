#include "structs/structs.hpp"
#include <EEPROM.h>
#include "config/config.hpp"


extern Config config;


// Load the configuration from the EEPROM
void loadConfig() {
    EEPROM.get(0, config);
    if (config.checkup != CONFIG_CHECKUP_BYTE) {
        resetConfig();
    }
}


// Save the configuration to the EEPROM
void saveConfig() {
    EEPROM.put(0, config);
}


// Create a new configuration and save it to the EEPROM
void resetConfig() {
    Config newConfig;
    EEPROM.put(0, newConfig);
    config = newConfig;
}
