#include "structs/structs.hpp"
#include <ChainableLED.h>
// #include <SD.h>  //SD
// #include <DS1307.h>  //clock
// #include <SoftwareSerial.h>  //Second Serial Port
// #include <Adafruit_BME280.h>  //Humidity/Pressure/Temperature


#define LED_PIN 7
#define LED_COUNT 1
// #define BME_SCK 13
// #define BME_MISO 12
// #define BME_MOSI 11
// #define BME_CS 10


extern Components components;
extern SystemState systemState;


void initComponents() {
    // LED
    ChainableLED leds(LED_PIN, LED_PIN + 1, LED_COUNT);
    leds.setColorRGB(0, systemState.ledColor1[0], systemState.ledColor1[1], systemState.ledColor1[2]);
    components.leds = &leds;

    // RTC Clock
    // DS1307 clock;
    // components.clock = &clock;

    // SD Card
    // File storageSD;
    // components.storageSD = &storageSD;

    // BME280 (I2C)
    // Adafruit_BME280 BME;
    // BME.begin(0x76);
    // components.BME = &BME;

    // GPS
    // SoftwareSerial SoftSerial(6, 7);
    // components.GPS = &SoftSerial;

    // Light Sensor
    pinMode(LIGHT_SENSOR_PIN, INPUT);

    // Buttons
    pinMode(RED_BUTTON_PIN, INPUT);
    pinMode(GREEN_BUTTON_PIN, INPUT);
}
