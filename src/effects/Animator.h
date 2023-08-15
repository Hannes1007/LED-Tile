#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <Adafruit_NeoPixel.h>

#include "PixelMapping.h"

class LedMatrix;
class LedDot;

class Animator
{
public:
  Animator(Adafruit_NeoPixel& pixels, const PixelMapping& mapping) : pixels_(pixels), mapping_(mapping) {}

  void animate(const LedMatrix& rainMatrix);
  void animate(const LedDot& ledDot);

  uint32_t Wheel(byte WheelPos);
  
private:
  Adafruit_NeoPixel& pixels_;
  const PixelMapping& mapping_;
};

#endif // ANIMATOR_H