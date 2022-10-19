#include <Arduino.h>

 /**
  * @brief Wait for a given amount of time or until a condition is met
  * @param sec The amount of time to wait in seconds
  * @param condition The condition to wait for. If the function returns true, the wait will stop
 */
void wait(unsigned int sec, bool (*condition)()) {
    unsigned long start = millis();
    while (condition() && millis() - start < (sec * 1000));
}
