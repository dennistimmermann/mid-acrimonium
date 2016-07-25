#include "Motion.h"

LSM6 imu;
unsigned long mtimer;

Motion::Motion(bool *_ptilted, float *_movement, float *_level) {
    Serial.println("instanced com");
	ptilted = _ptilted;
	movement = _movement;
	level = _level;
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
	mtimer = millis();
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

	if(mtimer + TILT_DELAY < millis()) {
        mtimer = millis();
        if(*ptilted == true) {
            digitalWrite(13, HIGH);
            *level = constrain(*level - TILT_DECREASE, 0.0, 100.0);
        } else {
           digitalWrite(13, LOW);
        }
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
