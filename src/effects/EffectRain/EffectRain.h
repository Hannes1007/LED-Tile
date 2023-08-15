#ifndef EFFECTRAIN_H
#define EFFECTRAIN_H

#include <Arduino.h>

#include "../IEffect.h"
#include "../../util/Configuration.h"

struct rainDropString
{
  int x;
  int y;
  int rValue;
  int gValue;
  int bValue;
  int step;
  int length;
  float speed;
};

class EffectRain : public IEffect
{
public:
  void init(int maxX, int maxY, int numberTiles, int res, Configuration* configuration);
  LedMatrix getMatrix() override;
  LedDot getDot() override;

private:
  Configuration* myConfiguration;
  int maxXCoordinates;
  int maxYCoordinates;
  int numberOfTiles;
  int resolution;
  int tick = 1;

  std::vector<rainDropString> listOfRainDropStrings;

  double getFunctionValue(float y, float step, int color);
  int randomizeColor(int currentColor, int percent);
};

#endif