#include "Sensors.h"

///////////////// constructor ///////////////////////////////

Sensors::Sensors()
{
    Serial.println("Sensors created");
};

///////////////// destructor ////////////////////////////////

Sensors::~Sensors()
{
    Serial.println("Sensors deleted");
}

/////////////////////////////////////////////////////////////
///////////////// public ////////////////////////////////////
/////////////////////////////////////////////////////////////

///////////////// setup /////////////////////////////////////

void Sensors::setup(Configuration* configuration)
{
  pinMode(pirSensorPin, INPUT);
  pinMode(photoSensorPin, INPUT); 

  myConfiguration = configuration;
  brightness = configuration->ledBrightness;
}

///////////////// read //////////////////////////////////////

int Sensors::read()
{
    int movement = digitalRead(pirSensorPin);
    int photo = analogRead(photoSensorPin);

    myConfiguration->lightSensorValueR = photo;
    myConfiguration->pirSensorTimeR = (currentTime - previousTime) / 1000; 

    if ((movement == HIGH) || (myConfiguration->lightSensorValue == 0) || (myConfiguration->pirSensorTime == 0))
    {
        //Serial.println("HIGH!!!");
        moved = true;
    }
    //Serial.println(photo);

    if(moved)
    {
        if (brightness < myConfiguration->ledBrightness)
        {
            dimm2Bright = true;
        }
    }

    timeoutTime = myConfiguration->pirSensorTime*1000;
    currentTime = millis(); 

    if((moved) || (currentTime > timeoutTime + previousTime))
    {
        previousTime = currentTime;
        if(moved)
        {
            moved = false;
        }
        else
        {
            bright2Dimm = true;
        }
    }

    if ((photo != 0) && (photo > myConfiguration->lightSensorValue))
    {
        dimm2Bright = false;
        bright2Dimm = true;
    }

    if(dimm2Bright)
    {
        if (brightness < myConfiguration->ledBrightness)
        {
            brightness += 1;
            bright2Dimm = false;
        }
        else
        {
            dimm2Bright = false;
        }
    }
    else if (bright2Dimm)
    {
        if(brightness > lowBrightness)
        {
            brightness -= 1;
        }
        else
        {
            bright2Dimm = false;
        }
    }
    return brightness;
}