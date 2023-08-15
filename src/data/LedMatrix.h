#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <vector>
#include <cstddef>

#include "Color.h"

using ColorMatrix = std::vector<std::vector<Color>>;

class LedMatrix
{
public:
  LedMatrix(size_t maxX, size_t maxY) : ledMatrix_(maxX, std::vector<Color>{maxY}) {}

  const Color& getMatrixLed(size_t x, size_t y) const;
  
  void setMatrixLed(size_t x, size_t y, const Color& c);
  void reset();
  
private:
  ColorMatrix ledMatrix_;
};

#endif