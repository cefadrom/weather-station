#include <Arduino.h>


#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255
#define ORANGE 255, 64, 0
#define YELLOW 255, 255, 0


void setContiniousLed(byte r, byte g, byte b);
void setBlinkingLed(byte r1, byte g1, byte b1, byte r2, byte g2, byte b2);
void setLongBlinkingLed(byte r1, byte g1, byte b1, byte r2, byte g2, byte b2);
