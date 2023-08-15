#ifndef COLOR_H
#define COLOR_H

#include <Arduino.h>


class Color
{
public:
  Color() : Color(0, 0, 0) {}
  Color(int r, int g, int b) : r_(r), g_(g), b_(b) {}

  int getR() const;
  int getG() const;
  int getB() const;

  Color hex2color(String hex);
  String color2hex(Color color);

private:
  int r_;
  int g_; 
  int b_;
};

#endif // COLOR_H