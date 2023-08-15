#include "Animator.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "data/LedMatrix.h"
#include "data/LedDot.h"

void Animator::animate(const LedMatrix& rainMatrix)
{
  for (int x = 0; x < mapping_.getMatrixMaxX(); x++)
  {
    for (int y = 0; y < mapping_.getMatrixMaxY(); y++)
    {
      try
      {
        pixels_.setPixelColor(mapping_.getLedId(x,y),
                          rainMatrix.getMatrixLed(x,y).getR(), 
                          rainMatrix.getMatrixLed(x,y).getG(), 
                          rainMatrix.getMatrixLed(x,y).getB());
      }
      catch(const std::exception& e)
      {
        Serial.println(e.what());
      }
    }
     
  }
  pixels_.show();
  //delay(10);
}

void Animator::animate(const LedDot& ledDot)
{
  pixels_.setPixelColor(mapping_.getLedId(ledDot.myX,ledDot.myY), ledDot.myColor.getR(), ledDot.myColor.getG(), ledDot.myColor.getB());
  pixels_.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Animator::Wheel(byte WheelPos)
{
  if (WheelPos < 85)
  {
    return pixels_.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170)
  {
    WheelPos -= 85;
    return pixels_.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else
  {
    WheelPos -= 170;
    return pixels_.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

