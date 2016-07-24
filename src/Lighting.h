#ifndef _ACRIMONIUM_LIGHTING_H
#define _ACRIMONIUM_LIGHTING_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

/*
 * SETTINGS
 */
#define NUM_LEDS 	60
#define LEDS_X		12
#define LEDS_Y		5

#define DATA_PIN 	10
#define BRIGHTNESS 	50

class Lighting {
	// Adafruit_NeoPixel strip;
	float *level;
	float *movement;
public:
	Lighting(float *_level, float *_movement);
	void begin();
	void fillNoise();
	void run();
};

#endif
