#include "Lighting.h"

const int gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
};

const int stripOne[] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18
};
const int stripTwo[] ={
    58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,
};

const int stripThree[] = {
  19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
};
const int stripFour[] = {
  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44
};
const int stripFive[] = {
  45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57
};
const int stripSix[] = {
  77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89
};

#if DEVICE == FLASK
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS_X_F * LEDS_Y_F, 10, NEO_GRBW + NEO_KHZ800);
#elif DEVICE == CHALICE
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS_X_C * LEDS_Y_C, 10, NEO_GRBW + NEO_KHZ800);
#else
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(90, 10, NEO_GRBW + NEO_KHZ800);
#endif
uint16_t speed = 48;

uint16_t x;
uint16_t y;
uint16_t z;

#if DEVICE == FLASK
    uint8_t noise[LEDS_X_F][LEDS_Y_F];
#else
    uint8_t noise[LEDS_X_C][LEDS_Y_C];
#endif

bool animationRan = false;

Lighting::Lighting(float *_level, float *_movement) {
    level = _level;
    movement = _movement;
    Serial.println("instanced lighting");
    // strip.setBrightness(255);
}

void Lighting::begin() {
    strip.begin();
    strip.show();

    x = 0;
    y = 0;
    z = 0;
}

void Lighting::fillNoise(int _x, int _y) {
    for (size_t i = 0; i < _x; i++) {
        int xoffset = 100 * i;
        for (size_t j = 0; j < _y; j++) {
            int yoffset = 100 * j;
            noise[i][j] = inoise8(x + xoffset, y + yoffset, z);
        }
    }
    z += speed;
}

void Lighting::run() {

    #if DEVICE == FLASK
        // /**
        //  * ! FLASK BLINKENLIGHTS
        //  */
        fillNoise(LEDS_X_F, LEDS_Y_F);
        int _lvl = (LEDS_X_F * LEDS_Y_F) * (*level/100.0);
        float brightness = ((*movement+10)/100.0);
        brightness = brightness * (*level/100.0);
        for(int i = 0; i < LEDS_X_F; i++) {
            for(int j = 0; j < LEDS_Y_F; j++) {

                int c = j*(LEDS_X_F -1)+i;
                float brightness2 = constrain((_lvl - c) / (float)(LEDS_X_F -1), 0.0, 1.0);

                strip.setPixelColor(c, strip.Color(
                    0,
                    (int) ( (20+gamma[noise[i][j]]) * brightness),
                    0,
                    (int) (gamma[noise[i][j]] * brightness)
                ));
                // You can also explore other ways to constrain the hue used, like below
                // leds[XY(i,j)] = CHSV(ihue + (noise[j][i]>>2),255,noise[i][j]);
                strip.show();
            }
        }
        // /**
        //  * / FLASK BLINKENLIGHTS
        //  */
    #elif DEVICE == CHALICE
        /**
        * ! CHALICE BLINKENLIGHTS
        */
        fillNoise(LEDS_X_C, LEDS_Y_C);
        int _lvl = (LEDS_X_C * LEDS_Y_C) * (*level/100.0);
        for(int i = 0; i < LEDS_X_C; i++) {
            for(int j = 0; j < LEDS_Y_C; j++) {

                int c = j*(LEDS_X_C -1)+i;
                float brightness = constrain((_lvl - c) / (float)(LEDS_X_C -1), 0.0, 1.0);
                strip.setPixelColor(c, strip.Color(
                    0,
                    (int) ( (20+gamma[noise[i][j]]) * brightness),
                    0,
                    (int) (gamma[noise[i][j]] * brightness)
                ));
                // You can also explore other ways to constrain the hue used, like below
                // leds[XY(i,j)] = CHSV(ihue + (noise[j][i]>>2),255,noise[i][j]);
                strip.show();
            }
        }
        /**
        * / CHALICE BLINKENLIGHTS
        */
     #elif DEVICE == NECKLACE
        if(animationRan == false && *level > 10.0) {
            animationRan == true;
            swipe();
            fill(4);
            swipe();
            fill(8);
            swipe();
            fill(12);
            swoon();
        }

     #endif



    // int lvl = 0;
    //
    // int _lvl = (LEDS_X * LEDS_Y) * (lvl/100.0);
    // for(int i = 0; i < LEDS_X * LEDS_Y; i++) {
    //     float brightness = (_lvl - i) / 12.0;
    //     brightness = 255.0 * constrain(brightness, 0.0, 1.0);
    //     strip.setPixelColor(i, strip.Color(gamma[(int)brightness],0,0,0));
    //     strip.show();
    //     delay(5);
    // }
    // Serial.println("sup lighting");
    // for(int j = 0; j < 256 ; j++){
    //     for(uint16_t i=0; i<strip.numPixels(); i++) {
    //         strip.setPixelColor(i, strip.Color(gamma[j],gamma[j],0, gamma[j] ) );
    //     }
    //     delay(5);
    //     strip.show();
    // }
    //
    // for(int j = 255; j >= 0 ; j--){
    //     for(uint16_t i=0; i<strip.numPixels(); i++) {
    //         strip.setPixelColor(i, strip.Color(gamma[j],gamma[j],0, gamma[j] ) );
    //     }
    //     delay(5);
    //     strip.show();
    // }
    // float
    // for(int i=0;i<*level+2;i++) {
    //
    //     // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    //     strip.setPixelColor(i, strip.Color(0,150,0)); // Moderately bright green color.
    //     strip.show(); // This sends the updated pixel color to the hardware.
    //     delay(5); // Delay for a period of time (in milliseconds).
    // }
}

void Lighting::fill(int to) {
  for(int i = 0; i < to; i++) {
      strip.setPixelColor(stripThree[i], strip.Color(128,255,0, 64 ) );
      strip.setPixelColor(stripFour[i], strip.Color(128,255,0, 64 ) );
      strip.setPixelColor(stripFive[i], strip.Color(128,255,0, 64 ) );
      strip.setPixelColor(stripSix[i], strip.Color(128,255,0, 64 ) );
      strip.show();
      delay(10);
    }
}

void Lighting::swipe() {
    for(int i = 0; i < 19; i++) {
      strip.setPixelColor(stripOne[i], strip.Color(128,255,0, 64 ) );
      strip.setPixelColor(stripTwo[i], strip.Color(128,255,0, 64 ) );
      strip.show();
      delay(20);
    }
    for(int i = 0; i < 19; i++) {
      strip.setPixelColor(stripOne[i], strip.Color(0,0,0, 0 ) );
      strip.setPixelColor(stripTwo[i], strip.Color(0,0,0, 0 ) );
      strip.show();
      delay(20);
    }
}

void Lighting::swoon() {
    for(int j = 255; j >= 0; j--) {
        for(int i = 0; i < 13; i++) {
            strip.setPixelColor(stripThree[i], strip.Color((int)j/2,j,0, (int)j/4 ) );
            strip.setPixelColor(stripFour[i], strip.Color((int)j/2,j,0, (int)j/4 ) );
            strip.setPixelColor(stripFive[i], strip.Color((int)j/2,j,0, (int)j/4 ) );
            strip.setPixelColor(stripSix[i], strip.Color((int)j/2,j,0, (int)j/4 ) );
        }
        strip.show();
        delay(10);
    }
    cli();
    while( true ); //An empty loop.
}
