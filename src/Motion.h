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

#define SHAKE_INCREASE		15
#define SHAKE_DECREASE		3


class Motion {
	float *movement;
	bool *ptilted;
public:
	Motion(bool *_tilted, float *_movement);
	bool tilted;
	bool shaking;
	double x;
	void begin();
	void run();
	void watchTilt();
	void watchShake();
};

#endif
