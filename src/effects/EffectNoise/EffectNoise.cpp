#include "EffectNoise.h"
#include "../FastNoiseLite.h"

FastNoiseLite fastNoise;

// input variables
Color primaryColor = Color(255, 5, 0);
Color secondaryColor = Color(255, 100, 0); // gelb Color(255, 100, 0);
float diffPhi = 0.05;

void EffectNoise::init(int maxX, int maxY, int numberTiles, int res, Configuration* configuration)
{
  maxXCoordinates = maxX;
  maxYCoordinates = maxY;
  numberOfTiles = numberTiles;
  resolution = res;

  myConfiguration = configuration;

  ledMatrix = new LedMatrix{maxXCoordinates, maxYCoordinates};
  // setLedMatrixArray();
}

void EffectNoise::setLedMatrixArray()
{
  int three60 = 360 / diffPhi;
  Serial.print(three60);
  Serial.println("????????????????????????????????????????????????????????");

  Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  Serial.println(phi);
  for (int i = 0; i < three60; ++i)
  {

    Serial.println(i);

    LedMatrix led = LedMatrix{5, 5};

    /*

    x=1;
    y=0;
    t=0;

    for (int xm = 0; xm < maxXCoordinates; xm++)
    {
      for (int ym = 0; ym < maxYCoordinates; ym++)
      {
        n = sn.noise((x+xm*iX)*cos(phi), y, (x+xm*iX)*sin(phi));
        int brightness = (int)map(n*100, -100, 100, minBrightness, maxBrightness);

        r=0;
        g=0;
        b=0 ;

        r = (getXPos5Value(brightness,secondaryColor.getR()) + getCosinusValue(brightness, primaryColor.getR()))/2;
        g = (getXPos5Value(brightness,secondaryColor.getG()) + getCosinusValue(brightness, primaryColor.getG()))/2;
        b = (getXPos5Value(brightness,secondaryColor.getB()) + getCosinusValue(brightness, primaryColor.getB()))/2;

        Color c(r,g,b);
      ////// ledArray[i].setMatrixLed(xm,ym,c);

        y += iY;
      }
      x += iX;
    }
    */
    phi = phi + diffPhi;
    listOfLedMatrices.push_back(led);
  }
}

LedMatrix EffectNoise::getMatrix()
{
  iX = myConfiguration->effectNoiseResolution;
  iY = myConfiguration->effectNoiseResolution;
  iT = myConfiguration->effectNoiseSpeed / 20;

  primaryColor = myConfiguration->effectNoisePrimaryColor;
  secondaryColor = myConfiguration->effectNoiseSecondaryColor;

  // t += iT;
  //x = 10;
  
  //t = 0;

  x=0;
  for (int xm = 0; xm < maxXCoordinates; xm++)
  {
    y = 0;
    for (int ym = 0; ym < maxYCoordinates; ym++)
    {

      // n = sn.noise((x+xm*iX)*cos(phi), y, (x+xm*iX)*sin(phi));
      // int brightness = (int)map(n*100, -100, 100, minBrightness, maxBrightness);

      //iX = 0.05;
      //iY = 0.05;
     // diffPhi = 0.003;

      //float xd = (x + xm * iX) * cos(phi);
      //float yd = y;
      //float zd = (x + xm * iX) * sin(phi);

      n = fastNoise.GetNoise(x, y, t);
      int brightness = (int)((n+1)*127);

      r = 0;
      g = 0;
      b = 0;

      r = (getSinusValue(brightness, secondaryColor.getR()) + getCosinusValue(brightness, primaryColor.getR()));
      g = (getSinusValue(brightness, secondaryColor.getG()) + getCosinusValue(brightness, primaryColor.getG()));
      b = (getSinusValue(brightness, secondaryColor.getB()) + getCosinusValue(brightness, primaryColor.getB()));

      //Serial.print("Gruen getXPos5Value: "); Serial.print(getXPos5Value(brightness, secondaryColor.getG()));
      
      //Serial.print(t);
      //Serial.print("  brighness; "); Serial.print(brightness); Serial.print(" gruen:  "); Serial.print(g);
      //Serial.print("     gruen getSinusValue: "); Serial.print(getSinusValue(brightness, secondaryColor.getG()));
      //Serial.print("     gruen getCosinusValue: "); Serial.println(getCosinusValue(brightness, primaryColor.getG()));
      //Serial.print(brightness); Serial.print("   rot:"); Serial.println(r);

      Color c(r, g, b);
      ledMatrix->setMatrixLed(xm, ym, c);

      y += iY;
    }
    x += iX;
  }

    t = t + iT;
  //phi = phi + diffPhi;

  return *ledMatrix;
  ;
}

int EffectNoise::getCosinusValue(int brightness, int color)
{
  return ((cos(brightness * 0.0123 - PI) + 1) * 127) * color / 255;
}

int EffectNoise::getSinusValue(int brightness, int color)
{
  return ((sin((brightness-127)* 0.0123 - PI) + 1) * 127) * color / 255;
}

int EffectNoise::getXPos5Value(int brightness, int color)
{
  return (pow((brightness / 101.4), 6) * color / 255);
}

LedDot EffectNoise::getDot()
{
  return {};
}
