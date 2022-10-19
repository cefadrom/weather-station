#include <Arduino.h>
#include "structs/structs.hpp"


extern SystemState systemState;


void setLeds1(byte r, byte g, byte b) {
    systemState.ledColor1[0] = r;
    systemState.ledColor1[1] = g;
    systemState.ledColor1[2] = b;
}


void setLeds2(byte r, byte g, byte b) {
    systemState.ledColor2[0] = r;
    systemState.ledColor2[1] = g;
    systemState.ledColor2[2] = b;
}


void setContiniousLed(byte r, byte g, byte b) {
    systemState.blinkMode = 0;
    setLeds1(r, g, b);
}


void setBlinkingLed(byte r1, byte g1, byte b1, byte r2, byte g2, byte b2) {
    systemState.blinkMode = 1;
    setLeds1(r1, g1, b1);
    setLeds2(r2, g2, b2);
}


void setLongBlinkingLed(byte r1, byte g1, byte b1, byte r2, byte g2, byte b2) {
    systemState.blinkMode = 2;
    setLeds1(r1, g1, b1);
    setLeds2(r2, g2, b2);
}
