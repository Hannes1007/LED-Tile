#include "EffectBoids.h"
#include "EffectBoidsBoid.h"

 std::vector<EffectBoidsBoid> flock;


float alignValue = .5;
float cohesionValue = 1;
float seperationValue = 1;

int numberOfBoids = 5;

void EffectBoids::init(int maxX, int maxY, int numberTiles, int res)
{
  maxXCoordinates = maxX;
  maxYCoordinates = maxY;
  numberOfTiles = numberTiles;
  resolution = res;

  for (int i = 0; i < numberOfBoids; i++)
  {
    EffectBoidsBoid boid;
    boid.init(maxX, maxY);
    flock.push_back(boid);
  }

  ledMatrix = new LedMatrix{maxXCoordinates, maxYCoordinates}; 
}

LedMatrix EffectBoids::getMatrix()
{
  if(tick > 10)
  {
  ledMatrix->reset();
  for (int i = 0; i < flock.size(); i++)
  {
    flock[i].update();
    flock[i].flock(flock);
    flock[i].edges();
    
    ledMatrix->setMatrixLed(flock[i].show().get().at(0), flock[i].show().get().at(1),{50,0,255});
  }
  tick=1;
  }  
  tick++;
return *ledMatrix;
}

LedDot EffectBoids::getDot()
{
  return {};
}
