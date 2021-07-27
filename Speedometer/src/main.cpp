#include <Arduino.h>

// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Adafruit_NeoPixel.h>
//Adafruit_NeoPixel.h
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#include "led_setup.h"

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     14
//#define LED_PIN     14
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  48

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


int red_0_intensity , green_0_intensity , blue_0_intensity ; 
int red_1_intensity , green_1_intensity , blue_1_intensity;
long int color_scale;
long int reading;
uint32_t RGB_state;
long int reading_0;
long int reading_1;



/* ---------------------------- Functions --------------------------*/


// ---------------------------DetermineColor----------------
// takes a value from 0 to 1000 and outputs a 24bit rgb value , 0 =  green , 1000 = red
uint32_t determineColor(long int reading, int *red_intensity , int *green_intensity , int *blue_intensity) {

  uint32_t c = 0;
  
  *red_intensity = map(reading , 0 , 1000 , 0 , 255);
  *green_intensity = map(reading , 0 , 1000 , 255 , 0);
  *blue_intensity = 0;

  c = (*red_intensity<<16) + (*green_intensity<<8) + (*blue_intensity);

return c;
}




void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}



int ledBargraph(long int reading , int display) {
//takes a 0 - 1000 value and a display selector and decides which leds to turn on ( 0 display is left display , 1 is right display , leds = 0 to 23 , or 24 to 47)

int number_of_leds_on = 0;

if ( display == 0 ) {
  number_of_leds_on = map(reading , 0 , 1000 , 0 , 23 );
}

if ( display == 1) {
  number_of_leds_on = map(reading , 0 , 1000 , 24 , 47);
}

return number_of_leds_on;

}


void displays_show ( long int reading_0 , long int reading_1 ) {

  int rgb_display_0_color = 0;
  int display_0_led_count = 0;

  int rgb_display_1_color = 0;
  int display_1_led_count = 0;


  //take the 0 to 1000 reading , and work out what color the leds should be
  rgb_display_0_color = determineColor(reading_0 , &red_0_intensity , &green_0_intensity , &blue_0_intensity );
  //take the 0 to 1000 reading and work out how many leds should be on
  display_0_led_count = ledBargraph ( reading_0 , 0);

  //take the 0 to 1000 reading , and work out what color the leds should be
  rgb_display_1_color = determineColor(reading_1 , &red_1_intensity , &green_1_intensity , &blue_1_intensity );

  //take the 0 to 1000 reading and work out how many leds should be on
  display_1_led_count = ledBargraph ( reading_1 , 1);

  
  //turn on leds for display 0
  for( int j = 0; j<=display_0_led_count ; j++){
    strip.setPixelColor(j, rgb_display_0_color );
  }
  //make sure other leds are off ( otherwise they just remain as last state)
  if ( display_0_led_count != 23) {
    for( int j = display_0_led_count+1; j<=23 ; j++){
    strip.setPixelColor(j, 0);
  }
  }


  //turn on leds for display 0
  for( int j = 24; j<=display_1_led_count ; j++){
    strip.setPixelColor(j, rgb_display_1_color );
  }
  //make sure other leds are off ( otherwise they just remain as last state)
  if ( display_1_led_count != 47) {
    for( int j = display_1_led_count+1; j<=47 ; j++){
    strip.setPixelColor(j, 1);
  }
  }

  strip.show();


}



void setup() {





/* ------------------ Setuping up LED ------------------*/
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50);
  
  //Wipe Leds just for nice startup visual
  colorWipe(strip.Color(  0, 255,   0)     , 50); // Green
  colorWipe(strip.Color(  255, 0,  255)     , 50); // Pink

/* ------------------ End of Setuping up LED ------------------*/

}







void loop() {
 

// displays_show(reading_0 , reading_1);


 for( int i = 0; i<=1000; i++) {
   displays_show(i , i);
   delay(1);
 }

 for( int i = 1000; i>0; i--) {
   displays_show(i , i);
   delay(1);
 }


}
