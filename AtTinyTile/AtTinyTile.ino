#include <tinyNeoPixel_Static.h>
#include <ArduinoUniqueID.h>
#include "Wire.h"

uint8_t matrix[19][3] = {0};

// led
const int ledPin = 4;  // the number of the LED pin
bool ledState = false;  // ledState used to set the LED

//i2c wire
#define I2C_DEV_ADDR 0x55
uint32_t i = 0;
bool reading = false;

//unique id
int id = 0;

//neopixel
#define NUMLEDS 19
byte pixels[NUMLEDS * 3];
tinyNeoPixel leds = tinyNeoPixel(NUMLEDS, 1, NEO_GRB, pixels);

void onRequest()
{
  Wire.print(id);
}

void onReceive(int len)
{
  char returnString[len];
  char returnString2[len];
  int count = 0;

  while(Wire.available())
  {
    char c = Wire.read();
    returnString[count]= c;
    count++;
  }

  if(returnString[0] == 'E')
  {
    reading = false; 
  }
  else if (reading)
  {
    uint8_t a,b,c, f=1;
    for(int z; z < len; z++)
    {
      //leds.setPixelColor(1, 0, 10, 0);
      if(f == 1)
      {
        a=(uint8_t)returnString[z];
      }
      if(f == 2)
      {
        b=(uint8_t)returnString[z];
      }
      if(f == 3)
      {
        c=(uint8_t)returnString[z];
        f=0;
        /*Serial.print(a);
        Serial.print(b);
        Serial.print(c);

        Serial.print("zähl:");
        Serial.print(z/3);
        Serial.print("   ");*/
        int stelle = z/3;

        matrix[stelle][0] = a;
        matrix[stelle][1] = b;
        matrix[stelle][2] = c;
      }
      f++;
    }
    //Serial.println();
  }
  
  strncpy(returnString2, returnString, len);
  returnString2[count] = 0;
  int i = atoi(returnString2);
  if(i == id)
  {
    reading = true; 
  }

  ledState= !ledState;
  digitalWrite(ledPin, ledState);

  
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(1, OUTPUT);

  //Serial.begin(9600);

  leds.begin();


  int multiplier = 15;
  for (size_t i = 0; i < UniqueIDsize; i++)
  {
    id+=UniqueID[i]*multiplier;
    multiplier++;
  }
  //Serial.println(id);

  Wire.pins(2,3);
  Wire.begin((uint8_t)I2C_DEV_ADDR);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
}

void loop()
{
 /* leds.setPixelColor(0, 10, 0, 0); // first LED full RED
  leds.setPixelColor(1, 0, 10, 0);
  leds.setPixelColor(2, 0, 0, 10);
 leds.setPixelColor(3, 101, 100, 100);*/
// leds.show();

for (int i = 0 ; i < 19; i++) 
{
        leds.setPixelColor(i, matrix[i][0], matrix[i][1], matrix[i][2]);
        leds.show();
}
        //leds.setPixelColor(0, a, b, c);
        //leds.show();

}
