#ifndef PIXEL_MAPPING_H
#define PIXEL_MAPPING_H

#include <Arduino.h>

struct led
{
  int x;
  int y;
  int id;
};

class PixelMapping
{
public:
  void setLedId(String inputString);
  int getLedId(int xpos, int ypos) const;

  int getNumberOfTiles();
  int getNumberOfPixels();


  size_t getMatrixMaxX() const;
  size_t getMatrixMaxY() const;

private:
  static std::vector<String> splitStringToVector(String msg, char delimiter);

  String myInputString;

  std::vector<led> listOfLeds_;
  size_t matrixMaxX_;
  size_t matrixMaxY_;
};

#endif // PIXEL_MAPPING_H