/**
 * MID - Acrimonium
 *
 * 2016
 * Dennis Timmermann
 */

#define FLASK   0x100
#define CHALICE 0x101
#define NECKLACE 0x102

#define DEVICE FLASK     

#include "Arduino.h"
#include "Communication.h"
#include "Motion.h"
#include "Lighting.h"

#include <Adafruit_NeoPixel.h>

/*
 * SETTINGS GO HERTE
 */

#define LED         13  // onboard blinky

float level = 100.0;
bool tilted = false;
float movement = 0.0;

Motion motion(&tilted, &movement);
Communication communication(&level, &tilted);
Lighting lights(&level, &movement);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  communication.begin();
  lights.begin();
  motion.begin();
  // strip.begin();
  // strip.show();
}



// the loop function runs over and over again forever
void loop() {
    motion.run();
    communication.run();
    lights.run();

    // if(tilted == true) {
    //     digitalWrite(13, HIGH);
    // } else {
    //    digitalWrite(13, LOW);
    // }

    // Serial.println("hey");
    // delay(5);

    // digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    // delay(20);              // wait for a second
    // Serial.println("hey ");

    // motion.run();
    // if(motion.tilted == true) {
    //     digitalWrite(13, HIGH);
    // } else {
    //     digitalWrite(13, LOW);
    // }
    // lights.run();
    // digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    // delay(2000);              // wait for a second
}
