#ifndef SDCARD_H
#define SDCARD_H

#include <Arduino.h>
#include "Configuration.h"

class SdCard
{
public:
    SdCard();
    ~SdCard();

    //setup
    void setup(Configuration* configuration);
    String read(Configuration::Config config);

    struct configStruct {String var; String val;};

    void write();



private:
    Configuration* myConfiguration;
    Color myColor;

    String getValue(String data, char separator, int index);

  

};

#endif