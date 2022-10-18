#include <Arduino.h>


typedef struct Config {
    // Luminosity sensor
    byte LUMIN = 1;                  // 0 or 1
    unsigned short LUMIN_LOW = 255;  // 0 to 1023
    unsigned short LUMIN_HIGH = 768; // 0 to 1023
    // Air temperature sensor
    byte TEMP_AIR = 1;              // 0 or 1
    signed char MIN_TEMP_AIR = -10; // -40 to 85
    signed char MAX_TEMP_AIR = 60;  // -40 to 85
    // Humidity sensor
    byte HYGR = 1;              // 0 or 1
    signed char HYGR_MINT = 0;  // -40 to 85
    signed char HYGR_MAXT = 50; // -40 to 85
    // Pressure sensor
    byte PRESSURE = 1;                  // 0 or 1
    unsigned short PRESSURE_MIN = 850;  // 300 to 1100
    unsigned short PRESSURE_MAX = 1080; // 300 to 1100
} Config;


typedef struct SystemState {
} SystemState;


typedef struct Sensors {
} Sensors;
