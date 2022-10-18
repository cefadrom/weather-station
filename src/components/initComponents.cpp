#include "structs/structs.hpp"
#include <ChainableLED.h>
#include <stdlib.h>


#define LED_PIN 7
#define LED_COUNT 1


extern Components components;


void initComponents() {
    // Initialize the LEDs using malloc
    ChainableLED leds(LED_PIN, LED_PIN + 1, LED_COUNT);
    components.leds = &leds;
}
