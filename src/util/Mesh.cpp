/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-mesh-esp32-esp8266-painlessmesh/
  
  This is a simple example that uses the painlessMesh library: https://github.com/gmag11/painlessMesh/blob/master/examples/basic/basic.ino
*/

#include "painlessMesh.h"

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

Scheduler userScheduler; // to control your personal task
painlessMesh  myMesh;

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {
  String msg = "Hi from node1";
  msg += myMesh.getNodeId();
  myMesh.sendBroadcast( msg );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", myMesh.getNodeTime(),offset);
}

void update() {
  Serial.begin(115200);

//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  myMesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  myMesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  myMesh.onReceive(&receivedCallback);
  myMesh.onNewConnection(&newConnectionCallback);
  myMesh.onChangedConnections(&changedConnectionCallback);
  myMesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}




//#include "Mesh.h"
//
//#define   MESH_PREFIX     "meinMeshNetz"
//#define   MESH_PASSWORD   "geheimesPasswort"
//#define   MESH_PORT       5555
//
//Scheduler userScheduler; // to control your personal task
//painlessMesh  mesh;
//
//Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );
//
/////////////////// constructor ///////////////////////////////
//
//Mesh::Mesh()
//{
//    Serial.println("Mesh created");
//};
//
/////////////////// destructor ////////////////////////////////
//
//Mesh::~Mesh()
//{
//    Serial.println("Mesh deleted");
//}
//
///////////////////////////////////////////////////////////////
/////////////////// public ////////////////////////////////////
///////////////////////////////////////////////////////////////
//
/////////////////// setup /////////////////////////////////////
//
//void Mesh::setup()
//{
//  Serial.begin(115200);
//  Serial.println("initialize Mesh");
//}
//
/////////////////// update ////////////////////////////////////
//
//void Mesh::update()
//{  
//  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
//  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages
//
//  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
//  mesh.onReceive(&receivedCallback);
//  mesh.onNewConnection(&newConnectionCallback);
//  mesh.onChangedConnections(&changedConnectionCallback);
//  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
//
//  userScheduler.addTask( taskSendMessage );
//  taskSendMessage.enable();
//}
//
///////////////////////////////////////////////////////////////
/////////////////// private ///////////////////////////////////
///////////////////////////////////////////////////////////////
//
//void Mesh::sendMessage() {
//  String msg = "Hi from node1";
//  msg += mesh.getNodeId();
//  mesh.sendBroadcast( msg );
//  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
//}
//
//// Needed for painless library
//void Mesh::receivedCallback( uint32_t from, String &msg ) {
//  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
//}
//
//void newConnectionCallback(uint32_t nodeId) {
//    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
//}
//
//void changedConnectionCallback() {
//  Serial.printf("Changed connections\n");
//}
//
//void nodeTimeAdjustedCallback(int32_t offset) {
//    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
//}
//