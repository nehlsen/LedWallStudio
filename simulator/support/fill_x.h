#ifndef LEDWALLSTUDIO_FILL_X_H
#define LEDWALLSTUDIO_FILL_X_H

#include "CRGB.h"

void fill_solid( struct CRGB * leds, int numToFill, const struct CRGB& color);

void fill_gradient_RGB( CRGB* leds,
                        uint16_t startpos, CRGB startcolor,
                        uint16_t endpos,   CRGB endcolor );

void fill_gradient_RGB( CRGB* leds, uint16_t numLeds, const CRGB& c1, const CRGB& c2);
void fill_gradient_RGB( CRGB* leds, uint16_t numLeds, const CRGB& c1, const CRGB& c2, const CRGB& c3);
void fill_gradient_RGB( CRGB* leds, uint16_t numLeds, const CRGB& c1, const CRGB& c2, const CRGB& c3, const CRGB& c4);

#endif //LEDWALLSTUDIO_FILL_X_H
