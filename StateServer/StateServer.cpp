//
// Created by erwin on 9-7-19.
//

#include "includes/StateServer.h"

const char *stateToString(enum States states)
{
    static const char *strings[] = { "IDLE", "WALKING", "GRABBING"};

    return strings[states];
}

long getCurrentSecond(){
    struct timespec tms;
    clock_gettime(CLOCK_REALTIME, &tms);

    return tms.tv_sec;
}

void *computerVisionThread(void* thread_arg){
    auto stateServer = (StateServer*)thread_arg;

    printf("Waiting for connection from the detection manager.\n");
    stateServer->computerVision->waitForClient();
    printf("Detection manager connected!\n");

    long distance;
    char *eptr;

    while(1){
        // Ask for the distance from the computer vision client
        stateServer->computerVision->sendToClient("ask_distance");

        // Wait until you get it
        stateServer->computerVision->receiveFromClient();

        // Store the time that the latest receival has taken place in
        stateServer->last_receival_time = getCurrentSecond();

        printf("Received distance from computer vision client: %s\n", stateServer->computerVision->buffer);

        // Try to store the distance in a long
        distance = strtol(stateServer->computerVision->buffer, &eptr, 10);

        if(errno != EINVAL){
            // If the distance is larger than GRABBING_DISTANCE then keep walking
            if(distance > GRABBING_DISTANCE){
                stateServer->currentState = States::WALKING;
            }else if(distance >= 0 && distance <= GRABBING_DISTANCE){
                // If the distance is between 0 and grabbing distance start grabbing the cup
                stateServer->currentState = States::GRABBING;
            }else if(distance < 0){
                // If the distance is smaller than 0 it means that no cup was detected. Start idling.
                stateServer->currentState = States::IDLE;
            }
        }

        usleep(100*1000); //Sleep for 100ms
    }
}

void *motionManagerThread(void* thread_arg){
    auto stateServer = (StateServer*)thread_arg;

    printf("Waiting for connection from the motion manager.\n");
    stateServer->motionManager->waitForClient();
    printf("Motion manager connected!\n");

    while(1){
        if(getCurrentSecond() - stateServer->last_receival_time > 3){
            printf("Amount since last data is 3 seconds or more!\n");
            stateServer->currentState = States::IDLE;
        }

        // Read the buffer from the client
        stateServer->motionManager->receiveFromClient();

        // If the motion manager asks for an update, pass the current state to him
        if(strncmp(stateServer->motionManager->buffer, "ask_state", 9) == 0){
            stateServer->motionManager->sendToClient(stateToString(stateServer->currentState));
        }
        usleep(100*1000); //Sleep for 100ms
    }
}

StateServer::StateServer() {
    this->computerVision = new ConnectionServer(8080);
    this->motionManager = new ConnectionServer(8081);

    // Starting state is IDLE
    this->currentState = States::IDLE;

    pthread_attr_t threadAttr;
    pthread_t cvThread, mmThread;
    sched_param lowPriority;

    pthread_attr_init(&threadAttr);

    lowPriority.sched_priority = 60;

    pthread_attr_setschedparam(&threadAttr, &lowPriority);
    pthread_attr_setschedpolicy(&threadAttr, SCHED_FIFO);

    pthread_create(&cvThread, &threadAttr, computerVisionThread, this);
    pthread_create(&mmThread, &threadAttr, motionManagerThread, this);

    pthread_join(cvThread, nullptr);
    pthread_join(mmThread, nullptr);
}

StateServer::~StateServer() {
    delete this->computerVision;
    delete this->motionManager;
}



