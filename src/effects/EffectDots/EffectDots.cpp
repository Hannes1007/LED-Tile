#include "EffectDots.h"

void EffectDots::init(int maxX, int maxY, int numberTiles, int res, Configuration* configuration)
{
  maxXCoordinates = maxX;
  maxYCoordinates = maxY;
  numberOfTiles = numberTiles;
  resolution = res;

  myConfiguration = configuration;

 // ledMatrix = new LedMatrix{maxXCoordinates, maxYCoordinates}; 
  ledDot = new LedDot();
}

LedMatrix EffectDots::getMatrix()
{
  return {0, 0};
}
LedDot EffectDots::getDot()
{
  //input variables
  int maxDropsPerTile = 3;
  int maxDropLength = 5;
  int rValueStart = 10;
  int gValueStart = 150;
  int bValueStart = 250;        
  int randomPercent = 30;

 // LedMatrix ledMatrix {maxXCoordinates, maxYCoordinates}; 


  //private variables
  int startX = random(0, maxXCoordinates);
  int startY = random(0, maxYCoordinates);

  float brightness = random(1, 10);
  int ratio = random(0, 5);

  int r, g, b;

  if (ratio == 0)
  {
    r = (myConfiguration->effectDotsSecondaryColor.getR() + random(10)) * brightness / 10;
    g = (myConfiguration->effectDotsSecondaryColor.getG() + random(10)) * brightness / 10;
    b = (myConfiguration->effectDotsSecondaryColor.getB() + random(10)) * brightness / 10;
  }
  else
  {
    r = (myConfiguration->effectDotsPrimaryColor.getR() + random(10)) * brightness / 10;
    g = (myConfiguration->effectDotsPrimaryColor.getG() + random(10)) * brightness / 10;
    b = (myConfiguration->effectDotsPrimaryColor.getB() + random(10)) * brightness / 10;
  }

 // ledMatrix->setMatrixLed(startX, startY,{r,g,b});
  ledDot->setDot(startX, startY,{r,g,b});        
return  *ledDot; //*ledMatrix;
}


