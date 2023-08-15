#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Arduino.h>
#include "data\Color.h"

class Configuration
{
    public:
        enum class Effect
        {
            None,
            rain,
            dots,
            boids,
            noise,
        };

        enum class sensorType
        {
            None,
            pir,
            photo,
        };

        enum class Config
        {
            //general
            None,

            //web page
            wifiSSID,
            wifiPWD,
            webName,

            //sensors
            lightSensorValue,
            pirSensorTime,

            //led general
            ledString,
            ledBrightness,

            //effect dots
            effectDotsActive,
            effectDotsPrimaryColor,
            effectDotsSecondaryColor,

            //effect rain
            effectRainActive,
            effectRainPrimaryColor,
            effectRainSecondaryColor,
            effectRainAmount,
            effectRainSpeed,

            //effect noise
            effectNoiseActive,
            effectNoisePrimaryColor,
            effectNoiseSecondaryColor,
            effectNoiseResolution,
            effectNoiseSpeed,

        };

        String getConfigName(Config config)
        {
            //general
            if(config == Config::None) {return "None";}

            //web page
            else if(config == Config::wifiSSID) {return "wifiSSID";}
            else if(config == Config::wifiPWD) {return "wifiPWD";}
            else if(config == Config::webName) {return "webName";}

            //sensors
            else if(config == Config::lightSensorValue) {return "lightSensorValue";}
            else if(config == Config::pirSensorTime) {return "pirSensorTime";}

            //led general
            else if(config == Config::ledString) {return "ledString";}
            else if(config == Config::ledBrightness) {return "ledBrightness";}
            
            //effect dots
            else if(config == Config::effectDotsActive) {return "effectDotsActive";}
            else if(config == Config::effectDotsPrimaryColor) {return "effectDotsPrimaryColor";}
            else if(config == Config::effectDotsSecondaryColor) {return "effectDotsSecondaryColor";}

            //effect rain
            else if(config == Config::effectRainActive) {return "effectRainActive";}
            else if(config == Config::effectRainPrimaryColor) {return "effectRainPrimaryColor";}
            else if(config == Config::effectRainSecondaryColor) {return "effectRainSecondaryColor";}
            else if(config == Config:: effectRainAmount) {return "effectRainAmount";}
            else if(config == Config::effectRainSpeed) {return "effectRainSpeed";}

            //effect noise
            else if(config == Config::effectNoiseActive) {return "effectNoiseActive";}
            else if(config == Config::effectNoisePrimaryColor) {return "effectNoisePrimaryColor";}
            else if(config == Config::effectNoiseSecondaryColor) {return "effectNoiseSecondaryColor";}
            else if(config == Config::effectNoiseResolution) {return "effectNoiseResolution";}
            else if(config == Config::effectNoiseSpeed) {return "effectNoiseSpeed";}
            
            else {return "None";}
        };

        ///////// will be saved on sdCard ////////////////////////////

        //web page
        String wifiSSID;
        String wifiPWD;
        String webName;

        //sensors
        int lightSensorValue;
        int pirSensorTime;

        //led general
        String ledString;
        int ledBrightness;

        //effect dots
        bool effectDotsActive;
        Color effectDotsPrimaryColor;
        Color effectDotsSecondaryColor;

        //effect rain
        bool effectRainActive;
        Color effectRainPrimaryColor;
        Color effectRainSecondaryColor;
        int effectRainAmount;
        int effectRainSpeed;

        //effect noise
        bool effectNoiseActive;
        Color effectNoisePrimaryColor;
        Color effectNoiseSecondaryColor;
        int effectNoiseResolution;
        int effectNoiseSpeed;

        ///////// temp values - will not saved on sdCard /////////////

        int lightSensorValueR;
        int pirSensorTimeR;

};

#endif