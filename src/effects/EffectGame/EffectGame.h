#ifndef EFFECTGAME_H
#define EFFECTGAME_H

#include <Arduino.h>

#include "../IEffect.h"

class EffectGame : public IEffect
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

  int currentAmount = 0;

};

#endif