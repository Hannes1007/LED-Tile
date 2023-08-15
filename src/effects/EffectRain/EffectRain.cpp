#include "EffectRain.h"

void EffectRain::init(int maxX, int maxY, int numberTiles, int res, Configuration* configuration)
{
  maxXCoordinates = maxX;
  maxYCoordinates = maxY;
  numberOfTiles = numberTiles;

  myConfiguration = configuration;
}

LedMatrix EffectRain::getMatrix()
{
  // input variables
  int maxDropsPerTile = myConfiguration->effectRainAmount;//3;
  int maxDropLength = 5;
  int randomPercent = 10;
  
  //speed
  resolution = 100 - myConfiguration->effectRainSpeed;

  //color variables
  int ratio = random(0, 5);
  int rValueStart, gValueStart, bValueStart;
  if (ratio == 0)
  {
    rValueStart = myConfiguration->effectRainSecondaryColor.getR();
    gValueStart = myConfiguration->effectRainSecondaryColor.getG();
    bValueStart = myConfiguration->effectRainSecondaryColor.getB();
  }
  else
  {
    rValueStart = myConfiguration->effectRainPrimaryColor.getR();
    gValueStart = myConfiguration->effectRainPrimaryColor.getG();
    bValueStart = myConfiguration->effectRainPrimaryColor.getB();
  }

  LedMatrix ledMatrix{maxXCoordinates, maxYCoordinates};

  // private variables
  int startX = random(0, maxXCoordinates);
  int startY = random(0, maxYCoordinates);

  // variate color
  rValueStart = randomizeColor(rValueStart, randomPercent);
  gValueStart = randomizeColor(gValueStart, randomPercent);
  bValueStart = randomizeColor(bValueStart, randomPercent);

  // advance tick
  if (tick > resolution)
  {
    tick = 1;
  }
  else
  {
    tick++;
  }

  // insert new startPoint
  if (tick == random(0, resolution))
  {
    if (listOfRainDropStrings.size() < maxDropsPerTile * numberOfTiles)
    {
      rainDropString tempRainDropString;
      tempRainDropString.x = startX;
      tempRainDropString.y = startY;

      tempRainDropString.rValue = rValueStart;
      tempRainDropString.gValue = gValueStart;
      tempRainDropString.bValue = bValueStart;

      tempRainDropString.step = 1;
      tempRainDropString.length = maxDropLength;
      tempRainDropString.speed = (float)((rand() % 5) + 1) / 6;

      listOfRainDropStrings.push_back(tempRainDropString);
    }
  }

  // advance drop
  for (int i = 0; i < listOfRainDropStrings.size(); i++)
  {
    for (int y = 0; y < maxYCoordinates; y++)
    {
      if (
          (int(getFunctionValue(y + listOfRainDropStrings[i].y, (float)listOfRainDropStrings[i].step / resolution * listOfRainDropStrings[i].speed, listOfRainDropStrings[i].rValue)) > 10) ||
          (int(getFunctionValue(y + listOfRainDropStrings[i].y, (float)listOfRainDropStrings[i].step / resolution * listOfRainDropStrings[i].speed, listOfRainDropStrings[i].gValue)) > 10) ||
          (int(getFunctionValue(y + listOfRainDropStrings[i].y, (float)listOfRainDropStrings[i].step / resolution * listOfRainDropStrings[i].speed, listOfRainDropStrings[i].bValue)) > 10))
      {
        ledMatrix.setMatrixLed(listOfRainDropStrings[i].x, y,
                               {int(getFunctionValue(y + listOfRainDropStrings[i].y, (float)listOfRainDropStrings[i].step / resolution * listOfRainDropStrings[i].speed, listOfRainDropStrings[i].rValue)),
                                int(getFunctionValue(y + listOfRainDropStrings[i].y, (float)listOfRainDropStrings[i].step / resolution * listOfRainDropStrings[i].speed, listOfRainDropStrings[i].gValue)),
                                int(getFunctionValue(y + listOfRainDropStrings[i].y, (float)listOfRainDropStrings[i].step / resolution * listOfRainDropStrings[i].speed, listOfRainDropStrings[i].bValue))});
      }
    }

    listOfRainDropStrings[i].step++;
  }

  // delete if out of boundry
  for (int i = 0; i < listOfRainDropStrings.size(); i++)
  {
    if (-listOfRainDropStrings[i].y + (float)listOfRainDropStrings[i].step / resolution * listOfRainDropStrings[i].speed > (maxYCoordinates + listOfRainDropStrings[i].length))
    {
      listOfRainDropStrings.erase(listOfRainDropStrings.begin() + i);
    }
  }
  return ledMatrix;
}

int EffectRain::randomizeColor(int currentColor, int percent)
{
  int ran = random(-percent, percent);
  int returnColor = currentColor + ran;

  if(returnColor < 0 )
    returnColor = 0;
  if(returnColor > 255)
    returnColor = 255;

  return returnColor;
}

double EffectRain::getFunctionValue(float y, float step, int color)
{
  if (-y + step < 0.0)
  {
    return 0.0;
  }
  return ((185 * (-y + step) / ((-y + step) * (-y + step) * (-y + step) + 1))) * color / 100;
}

LedDot EffectRain::getDot()
{
  return {};
}
