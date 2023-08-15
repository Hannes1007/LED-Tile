#ifndef I_EFFECT_H
#define I_EFFECT_H

#include "data/LedMatrix.h"
#include "data/LedDot.h"

class IEffect
{
public:
  virtual ~IEffect() = default;

  virtual LedMatrix getMatrix() = 0;
  virtual LedDot getDot() = 0;
};

#endif // I_EFFECT_H