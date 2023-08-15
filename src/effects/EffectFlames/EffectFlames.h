#ifndef EFFECTFLAMES_H
#define EFFECTFLAMES_H

#include <Arduino.h>

#include "../IEffect.h"

class EffectFlames : public IEffect
{
public:
  void init(int maxX, int maxY, int numberTiles, int res);
  LedMatrix getMatrix() override;
  LedDot getDot() override;

private:
  LedMatrix* ledMatrix; 
  int maxXCoordinates;
  int maxYCoordinates;
  int numberOfTiles;
  int resolution;
  int tick = 1;
};

#endif