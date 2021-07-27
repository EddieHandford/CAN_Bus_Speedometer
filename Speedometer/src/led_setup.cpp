#include <Adafruit_NeoPixel.h>



// How many NeoPixels are attached to the Arduino?
//#define LED_COUNT  48

// NeoPixel brightness, 0 (min) to 255 (max)
//#define BRIGHTNESS 50

Adafruit_NeoPixel ledSetup (int LED_PIN , Adafruit_NeoPixel strip) {

//Adafruit_NeoPixel strip(48, LED_PIN, NEO_GRB + NEO_KHZ800);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

return strip; 


}