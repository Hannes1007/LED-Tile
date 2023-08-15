#include "WebPage.h"

///////////////////////////////////// static members /////////////////////////////////////

SdCard* WebPage::mySdCard;
Configuration* WebPage::myConfiguration;
Color* WebPage::myColor;

bool WebPage::writeSdCard = false;


// here you post WebPage pages to your homes intranet which will make page debugging easier
// as you just need to refresh the browser as opposed to reconnection to the WebPage server
#define USE_INTRANET

// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[2048];

// just some buffer holder for char operations
char buf[64];

// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;

// definitions of your desired intranet created by the ESP32
IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

// gotta create a server
WebServer server(80);

///////////////////////////////////// constructor ////////////////////////////////////////

WebPage::WebPage()
{
    Serial.println("WLan created");
};

///////////////////////////////////// destructor /////////////////////////////////////////

WebPage::~WebPage()
{
    Serial.println("WLan deleted");
}

////////////////////////////////////////// setup /////////////////////////////////////////

void WebPage::setup(Configuration* configuration, SdCard* sdCard) 
{
  mySdCard = sdCard;
  myConfiguration = configuration;

  // if your WebPage page or XML are large, you may not get a call back from the WebPage page
  // and the ESP will think something has locked up and reboot the ESP
  // not sure I like this feature, actually I kinda hate it
  // disable watch dog timer 0
  // maybe disable watch dog timer 1 if needed
  // disableCore1WDT();
  disableCore0WDT();

  // if you have this #define USE_INTRANET,  you will connect to your home intranet, again makes debugging easier
#ifdef USE_INTRANET

  char ssid_char[100];
  configuration->wifiSSID.toCharArray(ssid_char, configuration->wifiSSID.length()+1);
  char pwd_char[100];
  configuration->wifiPWD.toCharArray(pwd_char, configuration->wifiPWD.length()+1);
  char WebPageName_char[100];
  configuration->webName.toCharArray(WebPageName_char, configuration->webName.length()+1);

  Serial.print("Connecting to ");
  Serial.print(ssid_char); 
  Serial.print("with password: ");
  Serial.println(pwd_char); 

  WiFi.begin(ssid_char, pwd_char);

  if(!MDNS.begin(WebPageName_char)) 
  {
     Serial.println("Error starting mDNS");
     return;
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();
#endif

  // if you don't have #define USE_INTRANET, here's where you will creat and access point
  // an intranet with no internet connection. But Clients can connect to your intranet and see
  // the WebPage page you are about to serve up
#ifndef USE_INTRANET
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  Actual_IP = WiFi.softAPIP();
  Serial.print("IP address: "); Serial.println(Actual_IP);
#endif

  printWifiStatus();

  server.on("/", SendWebPagesite);
  server.on("/xml", SendXML);

  server.on("/UPDATE_SLIDER_BRIGHTNESS", UpdateSliderBrightness);
  server.on("/UPDATE_SLIDER_LIGHTSENSOR", UpdateSliderLightSensorValue);
  server.on("/UPDATE_SLIDER_PIRSENSOR", UpdateSliderPirSensorTime);
  server.on("/UPDATE_SLIDER_RAINAMOUNT", UpdateSliderRainAmount);
  server.on("/UPDATE_SLIDER_RAINSPEED", UpdateSliderRainSpeed);
  server.on("/UPDATE_SLIDER_NOISERESOLUTION", UpdateSliderNoiseResolution);
  server.on("/UPDATE_SLIDER_NOISESPEED", UpdateSliderNoiseSpeed);

  server.on("/UPDATE_DOTS_PCOLOR", UpdateDotsPColor);
  server.on("/UPDATE_DOTS_SCOLOR", UpdateDotsSColor);
  server.on("/UPDATE_RAIN_PCOLOR", UpdateRainPColor);
  server.on("/UPDATE_RAIN_SCOLOR", UpdateRainSColor);
  server.on("/UPDATE_NOISE_PCOLOR", UpdateNoisePColor);
  server.on("/UPDATE_NOISE_SCOLOR", UpdateNoiseSColor);
  
  server.on("/BUTTON_Rain", ProcessButtonRain);
  server.on("/BUTTON_Dots", ProcessButtonDots);
  server.on("/BUTTON_Noise", ProcessButtonNoise);

  server.begin();
}

///////////////////////////////////// read ///////////////////////////////////////////////

void WebPage::read() 
{
  // no matter what you must call this handleClient repeatidly--otherwise the WebPage page
  // will not get instructions to do something
  server.handleClient();
  writeOnSdCard();
}

void WebPage::writeOnSdCard() 
{
  currentTime = millis(); 
  if(currentTime > timeoutTime + previousTime)
  {
  if(writeSdCard == true)
    {
      mySdCard->write();
      previousTime = currentTime;

      Serial.println("Writing SD Card.");
      writeSdCard = false;
    }
  }
}

///////////////////////////////////// siders /////////////////////////////////////////////

void WebPage::UpdateSliderBrightness() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->ledBrightness = t_state.toInt();
  writeSdCard = true;
}
void WebPage::UpdateSliderLightSensorValue() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->lightSensorValue = t_state.toInt();
  writeSdCard = true;
}
void WebPage::UpdateSliderPirSensorTime() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->pirSensorTime = t_state.toInt();
  writeSdCard = true;
}
void WebPage::UpdateSliderRainAmount() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->effectRainAmount = t_state.toInt();
  writeSdCard = true;
}
void WebPage::UpdateSliderRainSpeed() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->effectRainSpeed = t_state.toInt();
  writeSdCard = true;
}
void WebPage::UpdateSliderNoiseResolution() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->effectNoiseResolution = t_state.toInt();
  writeSdCard = true;
}
void WebPage::UpdateSliderNoiseSpeed() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->effectNoiseSpeed = t_state.toInt();
  writeSdCard = true;
}

///////////////////////////////////// color picker ///////////////////////////////////////

//Dots
void WebPage::UpdateDotsPColor() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->effectDotsPrimaryColor = myColor->hex2color(t_state);
  writeSdCard = true;
}
void WebPage::UpdateDotsSColor() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->effectDotsSecondaryColor = myColor->hex2color(t_state);
  writeSdCard = true;
}

//Rain
void WebPage::UpdateRainPColor() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->effectRainPrimaryColor = myColor->hex2color(t_state);
  writeSdCard = true;
}
void WebPage::UpdateRainSColor() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->effectRainSecondaryColor = myColor->hex2color(t_state);
  writeSdCard = true;
}

//Noise
void WebPage::UpdateNoisePColor() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->effectNoisePrimaryColor = myColor->hex2color(t_state);
  writeSdCard = true;
}
void WebPage::UpdateNoiseSColor() 
{
  String t_state = server.arg("VALUE");
  server.send(200, "text/plain", "");
  myConfiguration->effectNoiseSecondaryColor = myColor->hex2color(t_state);
  writeSdCard = true;
}

///////////////////////////////////// butttons ///////////////////////////////////////////

void WebPage::ProcessButtonRain()
{
  server.send(200, "text/plain", ""); 
  myConfiguration->effectRainActive = true;
  myConfiguration->effectDotsActive = false;
  myConfiguration->effectNoiseActive = false;
  writeSdCard = true;
}

void WebPage::ProcessButtonDots() 
{
  server.send(200, "text/plain", "");
  myConfiguration->effectRainActive = false;
  myConfiguration->effectDotsActive = true;
  myConfiguration->effectNoiseActive = false;
  writeSdCard = true;
}

void WebPage::ProcessButtonNoise()
{
  server.send(200, "text/plain", ""); 
  myConfiguration->effectRainActive = false;
  myConfiguration->effectDotsActive = false;
  myConfiguration->effectNoiseActive = true;
  writeSdCard = true;
}

///////////////////////////////////// send complete webpage //////////////////////////////

void WebPage::SendWebPagesite() {

  Serial.println("sending WebPage page");
  server.send(200, "text/html", PAGE_MAIN);
}

///////////////////////////////////// send to webpage ////////////////////////////////////

void WebPage::SendXML() 
{
  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  sprintf(buf, "<BRIGHTNESSV>%d</BRIGHTNESSV>\n", myConfiguration->ledBrightness); strcat(XML, buf);
  sprintf(buf, "<LIGHTSENSORV>%d</LIGHTSENSORV>\n", myConfiguration->lightSensorValue); strcat(XML, buf);
  sprintf(buf, "<LIGHTSENSORVR>%d</LIGHTSENSORVR>\n", myConfiguration->lightSensorValueR); strcat(XML, buf);

  sprintf(buf, "<PIRSENSORV>%d</PIRSENSORV>\n", myConfiguration->pirSensorTime); strcat(XML, buf);
  sprintf(buf, "<PIRSENSORVR>%d</PIRSENSORVR>\n", myConfiguration->pirSensorTimeR); strcat(XML, buf);

  sprintf(buf, "<RAINAMOUNTV>%d</RAINAMOUNTV>\n", myConfiguration->effectRainAmount); strcat(XML, buf);
  sprintf(buf, "<RAINSPEEDV>%d</RAINSPEEDV>\n", myConfiguration->effectRainSpeed); strcat(XML, buf);
  sprintf(buf, "<NOISERESV>%d</NOISERESV>\n", myConfiguration->effectNoiseResolution); strcat(XML, buf);
  sprintf(buf, "<NOISESPEEDV>%d</NOISESPEEDV>\n", myConfiguration->effectNoiseSpeed); strcat(XML, buf);
  
  sprintf(buf, "<DOTSPCOLOR>%s</DOTSPCOLOR>\n", myColor->color2hex(myConfiguration->effectDotsPrimaryColor).c_str()); strcat(XML, buf);
  sprintf(buf, "<DOTSSCOLOR>%s</DOTSSCOLOR>\n", myColor->color2hex(myConfiguration->effectDotsSecondaryColor).c_str()); strcat(XML, buf);
  sprintf(buf, "<RAINPCOLOR>%s</RAINPCOLOR>\n", myColor->color2hex(myConfiguration->effectRainPrimaryColor).c_str()); strcat(XML, buf);
  sprintf(buf, "<RAINSCOLOR>%s</RAINSCOLOR>\n", myColor->color2hex(myConfiguration->effectRainSecondaryColor).c_str()); strcat(XML, buf);
  sprintf(buf, "<NOISEPCOLOR>%s</NOISEPCOLOR>\n", myColor->color2hex(myConfiguration->effectNoisePrimaryColor).c_str()); strcat(XML, buf);
  sprintf(buf, "<NOISESCOLOR>%s</NOISESCOLOR>\n", myColor->color2hex(myConfiguration->effectNoiseSecondaryColor).c_str()); strcat(XML, buf);

  myConfiguration->effectDotsActive == true ? strcat(XML, "<EFFECTDOTS>1</EFFECTDOTS>\n") : strcat(XML, "<EFFECTDOTS>0</EFFECTDOTS>\n");
  myConfiguration->effectRainActive == true ? strcat(XML, "<EFFECTRAIN>1</EFFECTRAIN>\n") : strcat(XML, "<EFFECTRAIN>0</EFFECTRAIN>\n");
  myConfiguration->effectNoiseActive == true ? strcat(XML, "<EFFECTNOISE>1</EFFECTNOISE>\n") : strcat(XML, "<EFFECTNOISE>0</EFFECTNOISE>\n");

  strcat(XML, "</Data>\n");

  //Serial.println(XML);
  server.send(200, "text/xml", XML);
}

///////////////////////////////////// wifi status ////////////////////////////////////////

void WebPage::printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}

// end of code