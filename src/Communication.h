#ifndef _ACRIMONIUM_COMMUNICATION_H
#define _ACRIMONIUM_COMMUNICATION_H

#include "config.h"
#include "Arduino.h"
#include <SPI.h>
#include <RFM69.h>    //get it here: https://www.github.com/lowpowerlab/rfm69

#if DEVICE == FLASK
    #define NODEID      1    // 1: Flask, 2: Chalice, 3: Necklace
    #define RECEIVER    2   // Flask -> Chalice -> Necklace
#elif DEVICE == CHALICE
    #define NODEID      2    // 1: Flask, 2: Chalice, 3: Necklace
    #define RECEIVER    3   // Flask -> Chalice -> Necklace
#elif DEVICE == NECKLACE
    #define NODEID      3    // 1: Flask, 2: Chalice, 3: Necklace
    #define RECEIVER    4   // Flask -> Chalice -> Necklace
#endif

#define FREQUENCY   RF69_433MHZ
#define ACK_TIME    30

#define RFM69_CS    8
#define RFM69_IRQ   7
#define RFM69_IRQN  4  // Pin 7 is IRQ 4!
#define RFM69_RST   4

typedef struct {
  int nodeId;
  int volume;
} Payload;

class Communication {
	float *level;
	bool *tilted;
public:
	Communication(float *_level, bool *_tilted);
	void begin();
	void run();
};

#endif
