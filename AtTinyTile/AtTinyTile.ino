#include <tinyNeoPixel_Static.h>
#include <ArduinoUniqueID.h>
#include "Wire.h"


// led
const int ledPin = 4;  // the number of the LED pin
bool ledState = false;  // ledState used to set the LED

//timer
//unsigned long previousMillis = 0;  // will store last time LED was updated
//const long interval = 1000;  // interval at which to blink (milliseconds)

//i2c wire
#define I2C_DEV_ADDR 0x55
uint32_t i = 0;
int count = 0;

//unique id
int id = 0;

//neopixel
#define NUMLEDS 19
byte pixels[NUMLEDS * 3];
tinyNeoPixel leds = tinyNeoPixel(NUMLEDS, 1, NEO_GRB, pixels);



void onRequest(){
  Wire.print(i++);
  Wire.print(" Packets.");
  //Serial.println("onRequest");
}

void onReceive(int len)
{
  
  char returnString[len];
  bool isADigit = true;
  
  while(Wire.available())
  {
    char c = Wire.read();
    if (!isdigit(c)) 
    {
      isADigit = false;
    } 
    returnString[count]= c;
    count++;
  }
  count= 0;
  if(isADigit)
  {
    //Serial.print ("it's a number: "); Serial.println( atoi(returnString));
  }
  else
  {
    //Serial.print ("it has letters: "); Serial.println(returnString);
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
  leds.setPixelColor(0, 10, 0, 0); // first LED full RED
  leds.setPixelColor(1, 0, 10, 0);
  leds.setPixelColor(2, 0, 0, 10);
  leds.setPixelColor(3, 0, 10, 10);
  leds.show();                   // LED turns on.
  delay(10);
}
