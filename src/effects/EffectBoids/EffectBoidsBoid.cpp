#include "EffectBoidsBoid.h"

  EffectBoidsBoid::EffectBoidsBoid() 
  {
    //too fast for small display
    //velocity.set(random(1, 3),random(1, 3));
    velocity.set(1,1);
    maxForce = 1;
    maxSpeed = 4;
  }

  void EffectBoidsBoid::init(int width, int height)
  {
    position.set(random(0, width),random(0, height));

    maxXCoordinates = width;
    maxYCoordinates = height;
  }

  void EffectBoidsBoid::edges() 
  {
    
    if (position.get().at(0) >= maxXCoordinates) 
    {
      position.set(0,position.get().at(1));
    } else if (position.get().at(0)  < 0) 
    {
      position.set(maxXCoordinates,position.get().at(1));
    }
    if (position.get().at(1)  >= maxYCoordinates)
    {
      position.set(position.get().at(0),0);
    } else if (position.get().at(1) < 0) 
    {
      position.set(position.get().at(0),maxYCoordinates);
    }
    
  }

  PVector EffectBoidsBoid::align(std::vector<EffectBoidsBoid> boids) 
  {
    int perceptionRadius = 3;
    PVector steering;
    int total = 0;
    
    for (int i = 0; i < boids.size(); i++) 
    {
      float d = sqrt(pow((position.get().at(0) - boids.at(i).position.get().at(0)),2) + pow((position.get().at(1) - boids.at(i).position.get().at(1)),2));
      if ((&boids.at(i) != this) &&  (d < perceptionRadius)) 
      {
        steering.add(boids.at(i).velocity);
        total++;
      }
    }
    if (total > 0) 
    {
      steering.div(total);
      steering.setMag(maxSpeed);
      steering.sub(velocity);
      steering.limit(maxForce);
    }
    
    return steering;
  }

  PVector EffectBoidsBoid::separation(std::vector<EffectBoidsBoid> boids) 
  {
    int perceptionRadius = 3;
    PVector steering;
    int total = 0;
    
     for (int i = 0; i < boids.size(); i++) 
     {
      float d = sqrt(pow((position.get().at(0) - boids.at(i).position.get().at(0)),2) + pow((position.get().at(1) - boids.at(i).position.get().at(1)),2));
      if ((&boids.at(i) != this) &&  (d < perceptionRadius)) 
      {
        PVector diff;
        diff.set(position.get().at(0), position.get().at(1));
        diff.sub(boids.at(i).position);

        float divisorF = d*d;
        int divisorI = (int)divisorF;
        diff.div((divisorI));
        steering.add(diff);
        
        total++;
      }
    }
    if (total > 0) 
    {
      steering.div(total);
      steering.setMag(maxSpeed);
      steering.sub(velocity);
      steering.limit(maxForce);
    }
    
    return steering;
  }

  PVector EffectBoidsBoid::cohesion(std::vector<EffectBoidsBoid> boids) 
  {
    int perceptionRadius = 5;
    PVector steering;
    int total = 0;
    
     for (int i = 0; i < boids.size(); i++) 
     {
      float d = sqrt(pow((position.get().at(0) - boids.at(i).position.get().at(0)),2) + pow((position.get().at(1) - boids.at(i).position.get().at(1)),2));
      if ((&boids.at(i) != this) &&  (d < perceptionRadius)) 
      {
        steering.add(boids.at(i).position);
        total++;
      }
    }
    if (total > 0) {
      steering.div(total);
      steering.sub(position);
      steering.setMag(maxSpeed);
      steering.sub(velocity);
      steering.limit(maxForce);
    }
    
    return steering;
  }

  void EffectBoidsBoid::flock(std::vector<EffectBoidsBoid> boids)
  {
    
    PVector alignmentVector = align(boids);
    PVector cohesionVector = cohesion(boids);
    PVector separationVector = separation(boids);

    //alignmentVector.mult(alignmentValue);
    //cohesionVector.mult(cohesionValue);
    //separationVector.mult(seperationValue);

    acceleration.add(alignmentVector);
    acceleration.add(cohesionVector);
    acceleration.add(separationVector);
    
  }

  void EffectBoidsBoid::update() 
  {
    position.add(velocity);

    
    velocity.add(acceleration);
    velocity.limit(maxSpeed);
    acceleration.mult(0);
    
  }

  PVector EffectBoidsBoid::show() 
  {
   return position;
  }
