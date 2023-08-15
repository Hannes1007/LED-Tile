#include "LedDot.h"
#include "Color.h"


const Color& LedDot::getDot() const
{
  return myColor;
}

void LedDot::setDot(size_t x, size_t y, const Color& c)
{
  myX = x;
  myY = y;
  myColor = c;
}


///////////////////////////////////// color functions ////////////////////////////////////

Color Color::hex2color(String hex)
{
    int r, g, b;
    sscanf(hex.c_str(), "%02x%02x%02x", &r, &g, &b);
 
    Color returnColor(r,g,b);
    return returnColor;
}

String Color::color2hex(Color color)
{
  String returnColor;

  char hexcol[16];
  snprintf(hexcol, sizeof hexcol, "%02x%02x%02x", color.getR(), color.getG(), color.getB());
  returnColor += hexcol;

  //Serial.print(color.getR()); Serial.print(" "); Serial.print(color.getG());  Serial.print(" "); Serial.println(color.getB());
  //Serial.println(returnColor);

  return returnColor;
}