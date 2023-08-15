#ifndef EFFECTDOTS_H
#define EFFECTDOTS_H

#include <Arduino.h>

#include "../IEffect.h"
#include "../../util/Configuration.h"

class EffectDots : public IEffect
{
public:
  void init(int maxX, int maxY, int numberTiles, int res, Configuration* configuration);
  LedDot getDot() override;
  LedMatrix getMatrix() override;

private:
 // LedMatrix* ledMatrix; 
  LedDot* ledDot;

  Configuration* myConfiguration;

  int maxXCoordinates;
  int maxYCoordinates;
  int numberOfTiles;
  int resolution;
  int tick = 1;
};

#endif