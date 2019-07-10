//
// Created by erwin on 9-7-19.
//

#ifndef STATESERVER_STATESERVER_H
#define STATESERVER_STATESERVER_H

#include "ConnectionServer.h"
#include <pthread.h>
#include <errno.h>
#include <time.h>

#define GRABBING_DISTANCE 30


enum States{
    IDLE,
    WALKING,
    GRABBING
};

// This is a connection server with support for one connection at a time. Which was tested as successful.
class StateServer{
public:
    long last_receival_time;

    ConnectionServer *computerVision, *motionManager;
    enum States currentState;

    StateServer();
    virtual ~StateServer();
};

#endif //STATESERVER_STATESERVER_H
