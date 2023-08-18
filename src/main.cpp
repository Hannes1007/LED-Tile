#include <Arduino.h>
#include <Credentials.h>

#include "util/Configuration.h"

#include "data/LedMatrix.h"
#include "effects/Animator.h"
#include "effects/PixelMapping.h"

#include "effects/EffectRain/EffectRain.h"
#include "effects/EffectDots/EffectDots.h"
#include "effects//EffectBoids/EffectBoids.h"
#include "effects//EffectNoise/EffectNoise.h"
#include "effects//EffectGame/EffectGame.h"

#include "util/OTA.h"

//#include "util/Mesh.cpp"



#include "painlessMesh.h"

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

Scheduler userScheduler2; // to control your personal task
painlessMesh  mesh;

// User stub
void sendMessage2() ; // Prototype so PlatformIO doesn't complain

Task taskSendMessage2( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage2 );

void sendMessage2() {
  String msg = "Hi from node1";
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );
  //taskSendMessage2.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
  taskSendMessage2.enable();
}

// Needed for painless library
void receivedCallback2( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback2(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback2() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback2(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}




///////////////////////////////////// global variables ///////////////////////////////////
int brightness = 5;

///////////////////////////////////////// NeoPixel ///////////////////////////////////////
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 14

// int delayval = 500; // delay for half a second
Adafruit_NeoPixel pixels;

/////////////////////////////////////////// WiFi /////////////////////////////////////////

//////////////////////////////////////// led matrix //////////////////////////////////////

//////////////////////////////////// function declaration ////////////////////////////////

void web();
void rainbow(uint8_t);
void colorChange(uint8_t);
void line();
void coordinates();
void ripples();
void dots();
void bright();

///////////////////////////////////////// classes ////////////////////////////////////////

Configuration* configuration = new Configuration();

EffectRain effectRain;
EffectDots effectDots;
EffectBoids effectBoids;
EffectNoise effectNoise;
EffectGame effectGame;

PixelMapping mapping;
Animator anim{pixels, mapping};

OTA* ota = new OTA();

//Mesh* mesh = new Mesh();

////////////////////////////////////////// setup /////////////////////////////////////////
void setup()
{

#if defined(__AVR_ATtiny85__)
  if (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif

  Serial.begin(115200);

  //OTA
  ota->setup(WIFI_SSID, WIFI_PW, "https://raw.githubusercontent.com/Hannes1007/LED-Tile/master/.pio/build/d1_mini/firmware.bin");
  pinMode(D8, INPUT);
  ota->update(true);

  //Mesh
  //mesh->setup();
  
//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler2, MESH_PORT );
  mesh.onReceive(&receivedCallback2);
  mesh.onNewConnection(&newConnectionCallback2);
  mesh.onChangedConnections(&changedConnectionCallback2);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback2);

  userScheduler2.addTask( taskSendMessage2 );
  taskSendMessage2.enable();
  

  // mapping
  
  // neopixels
  pixels = Adafruit_NeoPixel(mapping.getNumberOfPixels(), PIN, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  pixels.setBrightness(255);

  // wifi

  // init effects
  effectRain.init(mapping.getMatrixMaxX(), mapping.getMatrixMaxY(), mapping.getNumberOfTiles(), 10, configuration);
  effectDots.init(mapping.getMatrixMaxX(), mapping.getMatrixMaxY(), mapping.getNumberOfTiles(), 10, configuration);
  effectBoids.init(mapping.getMatrixMaxX(), mapping.getMatrixMaxY(), mapping.getNumberOfTiles(), 10);
  effectNoise.init(mapping.getMatrixMaxX(), mapping.getMatrixMaxY(), mapping.getNumberOfTiles(), 10, configuration);
  effectGame.init(mapping.getMatrixMaxX(), mapping.getMatrixMaxY(), mapping.getNumberOfTiles(), 10);

  Serial.println(mapping.getMatrixMaxX());
  Serial.println(mapping.getMatrixMaxY());
  Serial.println(mapping.getNumberOfTiles());
}

/////////////////////////////////////////// loop /////////////////////////////////////////
void loop()
{
  int led = LED_BUILTIN;
  int delayT = 1000;

  pinMode(led, OUTPUT); 

  while (true)
  {

    mesh.update();
    mesh.sendBroadcast("Test");


    int sensorVal = digitalRead(D8);
   // Serial.println(sensorVal);
    if (sensorVal == HIGH) 
    {
      ota->update(true);
    }

    //digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    //Serial.println("an");
    //delay(delayT);                       // wait for a second
    //digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    //Serial.println("aus");
    //delay(delayT);                       // wait for a second
  }
  

  if (configuration->effectRainActive == true)
  {
     anim.animate(effectRain.getMatrix());
  }
  else if (configuration->effectDotsActive == true)
  {
    anim.animate(effectDots.getDot());
  }
  else if (configuration->effectNoiseActive == true)
  {
    anim.animate(effectNoise.getMatrix());
  }
  /*else if (configuration-> == true)
  {
    anim.animate(effectRain.getMatrix());
  }*/
  

}




