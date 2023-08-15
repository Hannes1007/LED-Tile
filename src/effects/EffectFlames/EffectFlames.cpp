#include "EffectFlames.h"

void EffectFlames::init(int maxX, int maxY, int numberTiles, int res)
{
  maxXCoordinates = maxX;
  maxYCoordinates = maxY;
  numberOfTiles = numberTiles;
  resolution = res;

  ledMatrix = new LedMatrix{maxXCoordinates, maxYCoordinates}; 
}

LedMatrix EffectFlames::getMatrix()
{
  
return *ledMatrix;
}

LedDot EffectFlames::getDot()
{
  return {};
}

