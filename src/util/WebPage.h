#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <Arduino.h>
#include "Configuration.h"
#include "data\Color.h"
#include "util/SdCard.h"


#include <stdio.h>
#include <iostream>
#include <sstream>

#include <ESPmDNS.h>

#include <WiFi.h>       // standard library
#include <WebServer.h>  // standard library
#include <WiFiClientSecure.h>
#include "SuperMon.h"   // .h file that stores your html page code

class WebPage
{

enum class Effect
   {
     None,
     rain,
     dots,
   };


public:
    WebPage();
    ~WebPage();

    //setup
    void setup(Configuration* configuration, SdCard* sdCard);
    void read();
   
private:
    unsigned long currentTime = millis();
    unsigned long previousTime = 0; 
    const long timeoutTime = 5000;

    void printWifiStatus();
    void writeOnSdCard();


    static SdCard* mySdCard;
    static Configuration* myConfiguration;
    static Color* myColor;

    static bool writeSdCard;
    
    static void SendXML();
    static void SendWebPagesite();

    static void ProcessButtonDots();
    static void ProcessButtonRain();
    static void ProcessButtonNoise();

    static void UpdateDotsPColor();
    static void UpdateDotsSColor();
    static void UpdateRainPColor();
    static void UpdateRainSColor();
    static void UpdateNoisePColor();
    static void UpdateNoiseSColor();

    static void UpdateSliderBrightness();
    static void UpdateSliderLightSensorValue();
    static void UpdateSliderPirSensorTime();
    static void UpdateSliderRainAmount();
    static void UpdateSliderRainSpeed();
    static void UpdateSliderNoiseResolution();
    static void UpdateSliderNoiseSpeed();



};

#endif