#ifndef OTA_H
#define OTA_H

#include <Arduino.h>


class OTA
{
public:
    OTA();
    ~OTA();

    //setup
    void setup(String, String, String);

    //update
    void update(bool);

private:
    void setClock();
    void FirmwareUpdate(bool);
    void connect_wifi();
    void repeatedCall(bool);

    char ssid[100];
    char password[100];
    
    unsigned long previousMillis_2 = 0;
    unsigned long previousMillis = 0;        // will store last time LED was updated
    unsigned long interval = 10000;
    unsigned long mini_interval = 1000;
};

#endif