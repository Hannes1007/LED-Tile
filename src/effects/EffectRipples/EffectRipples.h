#ifndef EFFECTRIPPLES_H
#define EFFECTRIPPLES_H

#include <Arduino.h>

#include "../IEffect.h"

class EffectRipples : public IEffect
{
public:
  void init(int maxX, int maxY, int numberTiles, int res);
  LedMatrix getMatrix() override;
  LedDot getDot() override;

private:
  LedMatrix* ledMatrix; 
  LedMatrix* previous; 
  LedMatrix* current;  

  int maxXCoordinates;
  int maxYCoordinates;
  int numberOfTiles;
  int resolution;
  int tick = 1;
};

#endif