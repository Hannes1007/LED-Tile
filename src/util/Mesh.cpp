#include "Mesh.h"

#define   MESH_PREFIX     "meinMeshNetz"
#define   MESH_PASSWORD   "geheimesPasswort"
#define   MESH_PORT       5555

Scheduler userScheduler2; // to control your personal task
painlessMesh mesh2;

Task taskSendMessage2( TASK_SECOND * 1 , TASK_FOREVER, &Mesh::sendMessage2 );

///////////////// constructor ///////////////////////////////

Mesh::Mesh()
{
    Serial.println("Mesh created");
};

///////////////// destructor ////////////////////////////////

Mesh::~Mesh()
{
    Serial.println("Mesh deleted");
}

/////////////////////////////////////////////////////////////
///////////////// public ////////////////////////////////////
/////////////////////////////////////////////////////////////

///////////////// setup /////////////////////////////////////

void Mesh::setup()
{
  Serial.begin(115200);
  Serial.println("initialize Mesh");

  mesh2.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler2, MESH_PORT );
  mesh2.onReceive(&receivedCallback2);
  mesh2.onNewConnection(&newConnectionCallback2);
  mesh2.onChangedConnections(&changedConnectionCallback2);
  mesh2.onNodeTimeAdjusted(&nodeTimeAdjustedCallback2);

  userScheduler2.addTask( taskSendMessage2 );
  taskSendMessage2.enable();
}

///////////////// update ////////////////////////////////////

void Mesh::update2()
{  

  mesh2.update();
  //mesh2.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  //mesh2.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages
  //mesh2.setDebugMsgTypes( CONNECTION | SYNC ); // all types on
  //mesh2.setDebugMsgTypes(ERROR | CONNECTION);
  //mesh2.setDebugMsgTypes(SYNC);

  
}

///////////////// send message //////////////////////////////

void Mesh::broadcast(String msg, bool includeSelf)
{
  mesh2.sendBroadcast(msg,includeSelf); 
}

/////////////////////////////////////////////////////////////
///////////////// private ///////////////////////////////////
/////////////////////////////////////////////////////////////

void Mesh::sendMessage2() {
  String msg = "Hi from node1";
  msg += mesh2.getNodeId();
  mesh2.sendBroadcast( msg );
  taskSendMessage2.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

// Needed for painless library
void Mesh::receivedCallback2( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void Mesh::newConnectionCallback2(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void Mesh::changedConnectionCallback2() {
  Serial.printf("Changed connections\n");
}

void Mesh::nodeTimeAdjustedCallback2(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh2.getNodeTime(),offset);
}
