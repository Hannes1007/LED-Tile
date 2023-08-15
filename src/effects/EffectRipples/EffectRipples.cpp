#include "EffectRipples.h"

float dampening = 0.99;

void EffectRipples::init(int maxX, int maxY, int numberTiles, int res)
{
  maxXCoordinates = maxX;
  maxYCoordinates = maxY;
  numberOfTiles = numberTiles;
  resolution = res;

  ledMatrix = new LedMatrix{maxXCoordinates, maxYCoordinates}; 
}

LedMatrix EffectRipples::getMatrix()
{
/*  for (int i = 1; i < maxXCoordinates - 1; i++) 
  {
    for (int j = 1; j < maxYCoordinates - 1; j++) 
    {
        Color color;
        
        color = new Color()
        
        current[i][j] =  (
                          
                          previous[i - 1][j] +
                          previous[i + 1][j] +
                          previous[i][j - 1] +
                          previous[i][j + 1]) /
                            2 -
                          current[i][j];
      current[i][j] = current[i][j] * dampening;

      current->setMatrixLed(i,j,color); 


      // Unlike in Processing, the pixels array in p5.js has 4 entries
      // for each pixel, so we have to multiply the index by 4 and then
      // set the entries for each color component separately.
      let index = (i + j * cols) * 4;
      pixels[index + 0] = current[i][j];
      pixels[index + 1] = current[i][j];
      pixels[index + 2] = current[i][j];
    }
  }


  let temp = previous;
  previous = current;
  current = temp;

  ledMatrix = current;

return *ledMatrix;
*/
}

LedDot EffectRipples::getDot()
{
  return {};
}


