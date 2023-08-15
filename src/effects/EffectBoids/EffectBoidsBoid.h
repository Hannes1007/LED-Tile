#ifndef EFFECTBOIDSBOIDS_H
#define EFFECTBOIDSBOIDS_H

#include <Arduino.h>
#include "PVector.h"



class EffectBoidsBoid
{
public:
  EffectBoidsBoid();
  void init(int width, int height);


  void edges();
  PVector align(std::vector<EffectBoidsBoid> boids); 
  PVector separation(std::vector<EffectBoidsBoid> boids); 
  PVector cohesion(std::vector<EffectBoidsBoid> boids); 
  void flock(std::vector<EffectBoidsBoid> boids);
  void update();
  PVector show();



private:
  PVector position;  
  PVector velocity;
  PVector acceleration;
  int maxForce;
  int maxSpeed;

  int maxXCoordinates;
  int maxYCoordinates;
};

#endif