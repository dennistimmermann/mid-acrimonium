#ifndef _ACRIMONIUM_LIGHTING_H
#define _ACRIMONIUM_LIGHTING_H

#include "config.h"
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

/*
 * SETTINGS
 */
#define NUM_LEDS 	60
#define LEDS_X_F		8
#define LEDS_Y_F		11

#define LEDS_X_C		8
#define LEDS_Y_C		5

#define DATA_PIN 	10

class Lighting {
	// Adafruit_NeoPixel strip;
	float *level;
	float *movement;
public:
	Lighting(float *_level, float *_movement);
	void begin();
	void fillNoise(int _x, int _y);
	void run();

	void fill(int to);
	void swipe();
	void swoon();
};

#endif
