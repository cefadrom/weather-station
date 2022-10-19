#include "structs/structs.hpp"
#include <ChainableLED.h>
#include <stdlib.h>


#define LED_PIN 7
#define LED_COUNT 1


extern Components components;
extern SystemState systemState;


void initComponents() {
    // Initialize the LEDs using malloc
    ChainableLED leds(LED_PIN, LED_PIN + 1, LED_COUNT);
    leds.setColorRGB(0, systemState.ledColor1[0], systemState.ledColor1[1], systemState.ledColor1[2]);
    components.leds = &leds;
}
