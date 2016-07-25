#ifndef _ACRIMONIUM_MOTION_H
#define _ACRIMONIUM_MOTION_H

#include "Arduino.h"
#include <Wire.h>
#include <LSM6.h>

/*
 * SETTINGS
 */
#define TILTED_THRESHOLD	2000
#define SHAKE_THRESHOLD		8000

#define TILT_DELAY			33

#define SHAKE_INCREASE		15
#define SHAKE_DECREASE		1

#define TILT_DECREASE		4


class Motion {
	float *movement;
	bool *ptilted;
	float *level;
public:
	Motion(bool *_tilted, float *_movement, float *_level);
	bool tilted;
	bool shaking;
	double x;
	void begin();
	void run();
	void watchTilt();
	void watchShake();
};

#endif
