#include "Motion.h"

LSM6 imu;

Motion::Motion(bool *_ptilted, float *_movement) {
    Serial.println("instanced com");
	ptilted = _ptilted;
	movement = _movement;
	x = 0;
	tilted = false;
	shaking = false;
}

void Motion::begin() {
	Wire.begin();
	if (!imu.init()) {
		Serial.println("Failed to detect and initialize IMU!");
		while (1);
	}
	imu.enableDefault();
}

void Motion::run() {

	if(*movement > 99.0) {
		shaking = false;
	}

    // Serial.println("sup motion");
    imu.read();
	Serial.println(imu.a.x);
	watchTilt();
	watchShake();

	if(shaking == true) {
		*movement = constrain(*movement + SHAKE_INCREASE, 0.0, 100.0);
	} else {
		*movement = constrain(*movement - SHAKE_DECREASE, 0.0, 100.0);
	}
}

void Motion::watchTilt() {
	x = imu.a.x;
	if(imu.a.x < TILTED_THRESHOLD) {
		tilted = true;
		*ptilted = true;
	} else {
		tilted = false;
		*ptilted = false;
	}
}

void Motion::watchShake() {
	if(imu.g.x > SHAKE_THRESHOLD || imu.g.y > SHAKE_THRESHOLD || imu.g.z > SHAKE_THRESHOLD) {
		shaking = true;
	}
	// } else {
	// 	shaking = false;
	// }
}
