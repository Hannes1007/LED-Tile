#ifndef MESH_H
#define MESH_H

#include <Arduino.h>

#include "painlessMesh.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();

    //setup
    void setup();

    //update
    void update2();

    //
    void broadcast(String , bool);

    static void sendMessage2();

private:
    
    static void receivedCallback2( uint32_t from, String &msg );
    static void newConnectionCallback2(uint32_t nodeId);
    static void changedConnectionCallback2();
    static void nodeTimeAdjustedCallback2(int32_t offset);

    
};

#endif