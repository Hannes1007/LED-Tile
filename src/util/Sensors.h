#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "Configuration.h"

class Sensors
{
public:
    Sensors();
    ~Sensors();

    //setup
    void setup(Configuration* configuration);

    //read
    int read();

private:
    Configuration* myConfiguration;

    int pirSensorPin = 34;
    int photoSensorPin = 32;

    bool moved = true;

    int brightness = 10;
    int lowBrightness = 0;

    bool bright2Dimm = false;
    bool dimm2Bright = false;

    unsigned long currentTime = millis();
    unsigned long previousTime = 0; 
    int timeoutTime;
};

#endif