#include "LedMatrix.h"

#include "Color.h"

const Color& LedMatrix::getMatrixLed(size_t x, size_t y) const
{
  return ledMatrix_.at(x).at(y);
}

void LedMatrix::reset()
{
  for (auto& line : ledMatrix_) {
    for (auto& color : line) {
      color = Color {};
    }
  }
}

void LedMatrix::setMatrixLed(size_t x, size_t y, const Color& c)
{
  ledMatrix_.at(x).at(y) = c;
}
