#include <Arduino.h>
#include <ChainableLED.h>


#define CONFIG_CHECKUP_BYTE 123
#define RED_BUTTON_PIN 3
#define GREEN_BUTTON_PIN 2
#define BAUD_RATE 115200


typedef struct Config {
    // Checkup bytes to see if the config is valid
    byte checkup = CONFIG_CHECKUP_BYTE;
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
    // Measures
    unsigned int LOG_INTERVAL = 10;    // in seconds
    unsigned int TIMEOUT = 30;         // in seconds
    unsigned int MAX_FILE_SIZE = 4096; // in bytes
} Config;


typedef struct SystemState {
    // Functionning state
    byte currentMode = 0; // 0 for init ; 1 for standart ; 2 for eco ; 3 for
                          // config ; 4 for maintenance
    bool isEco = false;
    // Buttons
    byte redButtonPushCount = 0;
    byte greenButtonPushCount = 0;
    // LEDs
    byte ledColor1[3] = {0, 0, 0};
    byte ledColor2[3] = {0, 0, 0};
    byte blinkMode = 0; // 0 for continious, 1 for blink at equal time, 2 for
                        // the second color to be twice as long
    byte blinkCounter = 0;
} SystemState;


typedef struct Components {
    ChainableLED *leds;
} Components;
