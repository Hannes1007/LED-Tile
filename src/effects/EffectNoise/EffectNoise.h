#ifndef EFFECTNOISE_H
#define EFFECTNOISE_H

#include <Arduino.h>
#include "../SimplexNoise.h"

#include "../IEffect.h"
#include "../../util/Configuration.h"

class EffectNoise : public IEffect
{
public:
  void init(int maxX, int maxY, int numberTiles, int res, Configuration* configuration);
  LedMatrix getMatrix() override;
  LedDot getDot() override;

private:
  Configuration* myConfiguration;
  LedMatrix* ledMatrix; 
  std::vector<LedMatrix> listOfLedMatrices;

  int maxXCoordinates;
  int maxYCoordinates;
  int numberOfTiles;
  int resolution;
  int tick = 1;

  SimplexNoise sn;

  double n;
  float iX = 10;
  float iY = 10;
  float iT = 2;
  float x = 0.0;
  float y = 0.0;
  float t = 0.0;
  float phi = 0.0;

  int r;
  int g;
  int b;

  int getCosinusValue(int brightness, int color);
  int getSinusValue(int brightness, int color);

  int getXPos5Value(int brightness, int color);

  
  void setLedMatrixArray();



  int minBrightness = 0;
  int maxBrightness = 255;
};

#endif