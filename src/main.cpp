#include <Arduino.h>
#include "util/Configuration.h"

#include "data/LedMatrix.h"
#include "effects/Animator.h"
#include "effects/PixelMapping.h"

#include "effects/EffectRain/EffectRain.h"
#include "effects/EffectDots/EffectDots.h"
#include "effects//EffectBoids/EffectBoids.h"
#include "effects//EffectNoise/EffectNoise.h"
#include "effects//EffectGame/EffectGame.h"

///////////////////////////////////// global variables ///////////////////////////////////
int brightness = 5;

///////////////////////////////////////// NeoPixel ///////////////////////////////////////
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 14

// int delayval = 500; // delay for half a second
Adafruit_NeoPixel pixels;

/////////////////////////////////////////// WiFi /////////////////////////////////////////

//////////////////////////////////////// led matrix //////////////////////////////////////

//////////////////////////////////// function declaration ////////////////////////////////

void web();
void rainbow(uint8_t);
void colorChange(uint8_t);
void line();
void coordinates();
void ripples();
void dots();
void bright();

///////////////////////////////////////// classes ////////////////////////////////////////

Configuration* configuration = new Configuration();

EffectRain effectRain;
EffectDots effectDots;
EffectBoids effectBoids;
EffectNoise effectNoise;
EffectGame effectGame;

PixelMapping mapping;
Animator anim{pixels, mapping};

////////////////////////////////////////// setup /////////////////////////////////////////
void setup()
{

#if defined(__AVR_ATtiny85__)
  if (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif

  Serial.begin(115200);

  // mapping
  
  // neopixels
  pixels = Adafruit_NeoPixel(mapping.getNumberOfPixels(), PIN, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  pixels.setBrightness(255);

  // wifi

  // init effects
  effectRain.init(mapping.getMatrixMaxX(), mapping.getMatrixMaxY(), mapping.getNumberOfTiles(), 10, configuration);
  effectDots.init(mapping.getMatrixMaxX(), mapping.getMatrixMaxY(), mapping.getNumberOfTiles(), 10, configuration);
  effectBoids.init(mapping.getMatrixMaxX(), mapping.getMatrixMaxY(), mapping.getNumberOfTiles(), 10);
  effectNoise.init(mapping.getMatrixMaxX(), mapping.getMatrixMaxY(), mapping.getNumberOfTiles(), 10, configuration);
  effectGame.init(mapping.getMatrixMaxX(), mapping.getMatrixMaxY(), mapping.getNumberOfTiles(), 10);

  Serial.println(mapping.getMatrixMaxX());
  Serial.println(mapping.getMatrixMaxY());
  Serial.println(mapping.getNumberOfTiles());
}

/////////////////////////////////////////// loop /////////////////////////////////////////
void loop()
{
  int led = D4;
  int delayT = 100;
  
  while (true)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(delayT);                       // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(delayT);                       // wait for a second
  }
  

  if (configuration->effectRainActive == true)
  {
     anim.animate(effectRain.getMatrix());
  }
  else if (configuration->effectDotsActive == true)
  {
    anim.animate(effectDots.getDot());
  }
  else if (configuration->effectNoiseActive == true)
  {
    anim.animate(effectNoise.getMatrix());
  }
  /*else if (configuration-> == true)
  {
    anim.animate(effectRain.getMatrix());
  }*/
  

}

///////////////////////////////////////// animate ////////////////////////////////////////

///////////////////////////////////////// rainbow ////////////////////////////////////////

void rainbow(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256; j++)
  {
    for (i = 0; i < pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, anim.Wheel((i * 1 + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

/////////////////////////////////////// color change /////////////////////////////////////

void colorChange(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256; j++)
  {
    for (i = 0; i < pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, anim.Wheel(j));
    }
    pixels.show();
    delay(wait);
  }
}

