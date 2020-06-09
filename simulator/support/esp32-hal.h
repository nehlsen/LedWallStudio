#ifndef LEDWALLSTUDIO_SIMULATOR_SUPPORT_ESP32_HAL_H
#define LEDWALLSTUDIO_SIMULATOR_SUPPORT_ESP32_HAL_H

#include <cmath>

#define portTICK_PERIOD_MS 1
#define PI 3.1415926535897932384626433832795

int millis();
int esp_timer_get_time();
int constrain(int val, int min, int max);
int random8(int lim = 255);
int random16(int lim = 255*255);
using std::sin;

#endif //LEDWALLSTUDIO_SIMULATOR_SUPPORT_ESP32_HAL_H
