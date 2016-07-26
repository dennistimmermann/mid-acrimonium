#ifndef _ACRIMONIUM_CONFIG_H
#define _ACRIMONIUM_CONFIG_H


#define FLASK       0x100
#define CHALICE     0x101
#define NECKLACE    0x102

/**
 * SET DEVICE BEFORE FLASHING!
 */
#define DEVICE      NECKLACE   // FLASK CHALICE NECKLACE

/*
 * MOTION SETTINGS
 */
#define TILTED_THRESHOLD	2000
#define SHAKE_THRESHOLD		8000

#define TILT_DELAY			33

#define SHAKE_INCREASE		15
#define SHAKE_DECREASE		1

#define TILT_DECREASE		4


/*
 * COMMUNICATION SETTINGS
 */
#define NETWORKID   69  // Kappa
#define KEY         "addamsacrimonium"
#define COMMUNICATION_DELAY  33  // send tilted every X milliseconds

#endif
