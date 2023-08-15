#include "PixelMapping.h"

void PixelMapping::setLedId(String inputString)
{
  //initialize lisOfLeds and inputString
  myInputString = inputString;
  listOfLeds_ = std::vector<led>(getNumberOfPixels());

  //cut pads
  std::vector<String> pads = splitStringToVector(inputString, '-');

  for (int i = 0; i < pads.size(); i++)
  {
    //Serial.println(pads[i]);
  }

  //fill pad matrix
  int matrix[pads.size()][3];
  int matrixPads = pads.size();

  for (int i = 0; i < pads.size(); i++)
  {
    std::vector<String> values = splitStringToVector(pads[i], ',');
    for (int k = 0; k < values.size(); k++)
    {
      //Serial.println(values[k]);

      int result = 0;
      int l, len;
      len = values[k].length();
      for (l = 0; l < len; l++)
      {
        result = result * 10 + (values[k][l] - '0');
        //Serial.print("result ");
        //Serial.println(result);
      }
      matrix[i][k] = result;
    }
  }

  //sort matrix
  int sortedMatrix[matrixPads][3];
  for (int n = 0; n < matrixPads; n++)
  {
    for (int m = 0; m < matrixPads; m++)
    {
      if (matrix[n][0] == m)
      {
        sortedMatrix[m][0] = matrix[n][0];
        sortedMatrix[m][1] = matrix[n][1];
        sortedMatrix[m][2] = matrix[n][2];
      }
    }
  }

  //print pad matrix
  for (int n = 0; n < matrixPads; n++)
  {
    for (int g = 0; g < 3; g++)
    {
      if (g == 0)
      {
        //Serial.print("PadId: ");
        //Serial.print(sortedMatrix[n][g]);
      }
      if (g == 1)
      {
        //Serial.print("   PadX: ");
        //Serial.print(sortedMatrix[n][g]);
      }
      if (g == 2)
      {
        //Serial.print("   PadY: ");
        //Serial.println(sortedMatrix[n][g]);
      }
    }
  }

  for (int padId = 0; padId < matrixPads; padId++)
  {
    for (int ledNummer = 1; ledNummer < 19 + 1; ledNummer++)
    {
      led tempLed;
      tempLed.id = ledNummer + (padId)*19 - 1;

      //X is even
      if ((sortedMatrix[padId][1] & 1) == 0)
      {
        //Serial.print("Pad ");
        //Serial.print(padId);
        //Serial.print(" is even.");
        //Serial.print(" X: ");
        //Serial.print(sortedMatrix[padId][1]);
        //Serial.print(" Y: ");
        //Serial.println(sortedMatrix[padId][2]);

        if (ledNummer == 1)
        {
          tempLed.x = 3 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 4 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 2)
        {
          tempLed.x = 2 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 4 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 3)
        {
          tempLed.x = 1 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 4 + 5 * (sortedMatrix[padId][2]);
        }

        if (ledNummer == 4)
        {
          tempLed.x = 1 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 3 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 5)
        {
          tempLed.x = 2 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 3 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 6)
        {
          tempLed.x = 3 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 3 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 7)
        {
          tempLed.x = 4 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 3 + 5 * (sortedMatrix[padId][2]);
        }

        if (ledNummer == 8)
        {
          tempLed.x = 4 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 2 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 9)
        {
          tempLed.x = 3 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 2 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 10)
        {
          tempLed.x = 2 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 2 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 11)
        {
          tempLed.x = 1 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 2 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 12)
        {
          tempLed.x = 0 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 2 + 5 * (sortedMatrix[padId][2]);
        }

        if (ledNummer == 13)
        {
          tempLed.x = 1 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 1 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 14)
        {
          tempLed.x = 2 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 1 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 15)
        {
          tempLed.x = 3 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 1 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 16)
        {
          tempLed.x = 4 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 1 + 5 * (sortedMatrix[padId][2]);
        }

        if (ledNummer == 17)
        {
          tempLed.x = 3 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 0 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 18)
        {
          tempLed.x = 2 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 0 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 19)
        {
          tempLed.x = 1 + 4 * (sortedMatrix[padId][1]);
          tempLed.y = 0 + 5 * (sortedMatrix[padId][2]);
        }
      }
      //X is odd
      else
      {
        //Serial.print("Pad ");
        //Serial.print(padId);
        //Serial.print(" is odd");
        //Serial.print(" X: ");
        //Serial.print(sortedMatrix[padId][1]);
        //Serial.print(" Y: ");
        //Serial.println(sortedMatrix[padId][2]);

        if (ledNummer == 1)
        {
          tempLed.x = 7 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 6 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 2)
        {
          tempLed.x = 6 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 6 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 3)
        {
          tempLed.x = 5 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 6 + 5 * (sortedMatrix[padId][2]);
        }

        if (ledNummer == 4)
        {
          tempLed.x = 5 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 5 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 5)
        {
          tempLed.x = 6 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 5 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 6)
        {
          tempLed.x = 7 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 5 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 7)
        {
          tempLed.x = 8 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 5 + 5 * (sortedMatrix[padId][2]);
        }

        if (ledNummer == 8)
        {
          tempLed.x = 8 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 4 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 9)
        {
          tempLed.x = 7 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 4 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 10)
        {
          tempLed.x = 6 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 4 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 11)
        {
          tempLed.x = 5 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 4 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 12)
        {
          tempLed.x = 4 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 4 + 5 * (sortedMatrix[padId][2]);
        }

        if (ledNummer == 13)
        {
          tempLed.x = 5 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 3 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 14)
        {
          tempLed.x = 6 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 3 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 15)
        {
          tempLed.x = 7 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 3 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 16)
        {
          tempLed.x = 8 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 3 + 5 * (sortedMatrix[padId][2]);
        }

        if (ledNummer == 17)
        {
          tempLed.x = 7 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 2 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 18)
        {
          tempLed.x = 6 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 2 + 5 * (sortedMatrix[padId][2]);
        }
        if (ledNummer == 19)
        {
          tempLed.x = 5 + 4 * (sortedMatrix[padId][1] - 1);
          tempLed.y = 2 + 5 * (sortedMatrix[padId][2]);
        }
      }
      listOfLeds_[tempLed.id] = tempLed;
    }
  }

  //listOfLeds print
  for (const auto& oneLed : listOfLeds_)
  {
    //Serial.print("Led Nr: ");
    //Serial.print(oneLed.id);
    //Serial.print("   x: ");
    //Serial.print(oneLed.x);
    //Serial.print("   y: ");
    //Serial.println(oneLed.y);
  }

  matrixMaxX_ = std::max_element(listOfLeds_.begin(), listOfLeds_.end(), [](const led& lhs, const led& rhs) {
    return lhs.x < rhs.x + 1;
  })->x + 1;
  matrixMaxY_ = std::max_element(listOfLeds_.begin(), listOfLeds_.end(), [](const led& lhs, const led& rhs) {
    return lhs.y < rhs.y;
  })->y + 1;
}

int PixelMapping::getLedId(int xpos, int ypos) const
{
  auto ledIt = std::find_if(listOfLeds_.begin(), listOfLeds_.end(), [&](const led& elem) {
    return elem.x == xpos && elem.y == ypos;
  });
  return (ledIt != listOfLeds_.end()) ? ledIt->id : 9999;
}

size_t PixelMapping::getMatrixMaxX() const
{
  return matrixMaxX_;
}

size_t PixelMapping::getMatrixMaxY() const
{
  return matrixMaxY_;
}

std::vector<String> PixelMapping::splitStringToVector(String msg, char delimiter)
{
  std::vector<String> subStrings;
  int j = 0;
  for (int i = 0; i < msg.length(); i++)
  {
    if (msg.charAt(i) == delimiter)
    {
      subStrings.push_back(msg.substring(j, i));
      j = i + 1;
    }
  }
  subStrings.push_back(msg.substring(j, msg.length())); //to grab the last value of the string
  return subStrings;
}

int PixelMapping::getNumberOfPixels() 
{
  return getNumberOfTiles() * 19;
}

int PixelMapping::getNumberOfTiles() 
{
  int n = std::count(myInputString.begin(), myInputString.end(), '-') + 1;
  return n;
}

