#include "EffectGame.h"

//input variables
int change = true;


void EffectGame::init(int maxX, int maxY, int numberTiles, int res)
{
  maxXCoordinates = maxX;
  maxYCoordinates = maxY;
  numberOfTiles = numberTiles;
  resolution = res;

  ledMatrix = new LedMatrix{maxXCoordinates, maxYCoordinates}; 
}

LedMatrix EffectGame::getMatrix()
{
    /*if(currentAmount < numberOfTiles*9)
    {
        int startX = random(0, maxXCoordinates);
        int startY = random(0, maxYCoordinates);

        float brightness = random(1, 10);
        int r = (230 + random(20)) * brightness / 10;
        int g = (205 + random(50)) * brightness / 10;
        int b = (210 + random(30))*brightness/10;

        ledMatrix->setMatrixLed(startX, startY,{r,g,b}); 
        currentAmount++;
    }*/

    for (int x = 0; x < maxXCoordinates; x++)
    {
      for (int y = 0; y < maxYCoordinates; y++)
      {
          Color c(20,1,1);
          Color c2(1,20,1);
          if (change == true)
          {
            ledMatrix->setMatrixLed(x,y,c);
          }
          else
          {
              ledMatrix->setMatrixLed(x,y,c2);
          }
      }
    }

    if (change == true)
    {
        change = false;
    }
    else
    {
        change = true;
    }
   
 return *ledMatrix;;
}

LedDot EffectGame::getDot()
{
 return {};
}
