#ifndef LEDDOT_H
#define LEDDOT_H

#include <cstddef>

#include "Color.h"

class LedDot
{
public:
  LedDot() {}
  const Color& getDot() const;
  void setDot(size_t x, size_t y, const Color& c);
 
  size_t myX;
  size_t myY;
  Color myColor;

private:

};

#endif