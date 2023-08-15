#include "SdCard.h"

#include <SPI.h>
#include <SD.h> 

File Textdatei;

///////////////// enums /////////////////////////////////////
/*
enum direction
{
    down,
    up
};*/

///////////////// constructor ///////////////////////////////

SdCard::SdCard()
{
    Serial.println("SdCard created");
};

///////////////// destructor ////////////////////////////////

SdCard::~SdCard()
{
    Serial.println("SdCard deleted");
}

/////////////////////////////////////////////////////////////
///////////////// public ////////////////////////////////////
/////////////////////////////////////////////////////////////

///////////////// setup /////////////////////////////////////

void SdCard::setup(Configuration* configuration)
{
  Serial.println("initialize sd card");

  if (!SD.begin(5)) 
  {                           
    Serial.println("initialize failed!");
    return;
  }
  
  Serial.println("initialize sd card complete");

  myConfiguration = configuration;


  //web page
  myConfiguration->wifiSSID = read(Configuration::Config::wifiSSID);
  myConfiguration->wifiPWD = read(Configuration::Config::wifiPWD);
  myConfiguration->webName = read(Configuration::Config::webName);

  //sensors
  myConfiguration->lightSensorValue = read(Configuration::Config::lightSensorValue).toInt();
  myConfiguration->pirSensorTime = read(Configuration::Config::pirSensorTime).toInt();

  //led general
  myConfiguration->ledString = read(Configuration::Config::ledString);
  myConfiguration->ledBrightness = read(Configuration::Config::ledBrightness).toInt();

  //effect dots
  myConfiguration->effectDotsActive = (read(Configuration::Config::effectDotsActive) == "true") ? true : false;
  myConfiguration->effectDotsPrimaryColor = myColor.hex2color(read(Configuration::Config::effectDotsPrimaryColor));
  myConfiguration->effectDotsSecondaryColor = myColor.hex2color(read(Configuration::Config::effectDotsSecondaryColor));

  //effect rain
  myConfiguration->effectRainActive = (read(Configuration::Config::effectRainActive) == "true") ? true : false;
  myConfiguration->effectRainPrimaryColor = myColor.hex2color(read(Configuration::Config::effectRainPrimaryColor));
  myConfiguration->effectRainSecondaryColor = myColor.hex2color(read(Configuration::Config::effectRainSecondaryColor));
  myConfiguration->effectRainAmount = read(Configuration::Config::effectRainAmount).toInt();
  myConfiguration->effectRainSpeed = read(Configuration::Config::effectRainSpeed).toInt();


  //effect noise
  myConfiguration->effectNoiseActive = (read(Configuration::Config::effectNoiseActive) == "true") ? true : false;
  myConfiguration->effectNoisePrimaryColor = myColor.hex2color(read(Configuration::Config::effectNoisePrimaryColor));
  myConfiguration->effectNoiseSecondaryColor = myColor.hex2color(read(Configuration::Config::effectNoiseSecondaryColor));
  myConfiguration->effectNoiseResolution = read(Configuration::Config::effectNoiseResolution).toInt();
  myConfiguration->effectNoiseSpeed = read(Configuration::Config::effectNoiseSpeed).toInt();

}



///////////////// read //////////////////////////////////////

String SdCard::read(Configuration::Config config)
{
  Serial.println("read config");
  Textdatei = SD.open("/config.txt");
  if (Textdatei) 
  {
    String finalString;
    while (Textdatei.available())
    {            
      finalString.concat((char)Textdatei.read());          
    }
    Textdatei.close();    
    Serial.println(finalString); 
    Serial.println("finalString finished");   

    int n = std::count(finalString.begin(), finalString.end(), '=');
    configStruct listOfConfigs[n*2];

    for (int i = 0; i < n*2; i++)
    {
        if ( i % 2 == 0 )
        {
            listOfConfigs[i/2].var =  getValue(finalString, '=', i);
        }
        else
        {
            listOfConfigs[i/2].val =  getValue(finalString, '=', i);
            listOfConfigs[i/2].val.remove(listOfConfigs[i/2].val.length() - 1);
        }
    }

    for (int i = 0; i < n; i++)
    {
        Serial.print(listOfConfigs[i].var); Serial.print("      "); Serial.println(listOfConfigs[i].val);
        if (listOfConfigs[i].var == myConfiguration->getConfigName(config))
        {
            return listOfConfigs[i].val;
        }
    }
  } 
  else                                                           
  {
    Serial.println("could not open config.txt");     
    return "";
  }           
  return "";                
}

String SdCard::getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || data.charAt(i) == '\n' || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

///////////////// write /////////////////////////////////////

void SdCard::write()
{
  SD.remove("/config.txt");  
  Textdatei = SD.open("/config.txt", FILE_WRITE);  

  if (Textdatei) 
  { 
    Serial.println("writing in file");

    //web page
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::wifiSSID)); Textdatei.print("="); Textdatei.println(myConfiguration->wifiSSID);
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::wifiPWD)); Textdatei.print("="); Textdatei.println(myConfiguration->wifiPWD);
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::webName)); Textdatei.print("="); Textdatei.println(myConfiguration->webName);
    
    //sensors
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::lightSensorValue)); Textdatei.print("="); Textdatei.println(myConfiguration->lightSensorValue);
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::pirSensorTime)); Textdatei.print("="); Textdatei.println(myConfiguration->pirSensorTime);

    //led general
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::ledString)); Textdatei.print("="); Textdatei.println(myConfiguration->ledString);
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::ledBrightness)); Textdatei.print("="); Textdatei.println(myConfiguration->ledBrightness);

    //effect dots
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectDotsActive)); Textdatei.print("="); Textdatei.println((myConfiguration->effectDotsActive == true) ? "true" : "false");
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectDotsPrimaryColor)); Textdatei.print("="); Textdatei.println(myColor.color2hex(myConfiguration->effectDotsPrimaryColor));
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectDotsSecondaryColor)); Textdatei.print("="); Textdatei.println(myColor.color2hex(myConfiguration->effectDotsSecondaryColor));

    //effect rain
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectRainActive)); Textdatei.print("="); Textdatei.println((myConfiguration->effectRainActive == true) ? "true" : "false");
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectRainPrimaryColor)); Textdatei.print("="); Textdatei.println(myColor.color2hex(myConfiguration->effectRainPrimaryColor));
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectRainSecondaryColor)); Textdatei.print("="); Textdatei.println(myColor.color2hex(myConfiguration->effectRainSecondaryColor));
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectRainAmount)); Textdatei.print("="); Textdatei.println(myConfiguration->effectRainAmount);
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectRainSpeed)); Textdatei.print("="); Textdatei.println(myConfiguration->effectRainSpeed);

    //effect noise
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectNoiseActive)); Textdatei.print("="); Textdatei.println((myConfiguration->effectNoiseActive == true) ? "true" : "false");
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectNoisePrimaryColor)); Textdatei.print("="); Textdatei.println(myColor.color2hex(myConfiguration->effectNoisePrimaryColor));
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectNoiseSecondaryColor)); Textdatei.print("="); Textdatei.println(myColor.color2hex(myConfiguration->effectNoiseSecondaryColor));
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectNoiseResolution)); Textdatei.print("="); Textdatei.println(myConfiguration->effectNoiseResolution);
    Textdatei.print(myConfiguration->getConfigName(Configuration::Config::effectNoiseSpeed)); Textdatei.print("="); Textdatei.println(myConfiguration->effectNoiseSpeed);




    Textdatei.print("//end of file");

    Textdatei.close();
    Serial.println("writing in file finished");
    Serial.println();
  } 
  else 
  {  
    Serial.println("file not found");
  }
}