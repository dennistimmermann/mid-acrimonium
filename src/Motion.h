#ifndef _ACRIMONIUM_MOTION_H
#define _ACRIMONIUM_MOTION_H

#include "config.h"
#include "Arduino.h"
#include <Wire.h>
#include <LSM6.h>

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
