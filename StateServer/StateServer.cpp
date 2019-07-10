//
// Created by erwin on 9-7-19.
//

#include "includes/StateServer.h"

const char *stateToString(enum StateMachine stateMachine)
{
    static const char *strings[] = { "IDLE", "WALKING", "GRABBING"};

    return strings[stateMachine];
}

long getCurrentSecond(){
    struct timespec tms;
    clock_gettime(CLOCK_REALTIME, &tms);

    return tms.tv_sec;
}

void *computerVisionThread(void* thread_arg){
    auto stateServer = (StateServer*)thread_arg;

    printf("Waiting for connection from the detection manager.\n");
    stateServer->computerVision->waitForConnection();
    printf("Detection manager connected!\n");

    long distance;
    char *eptr;

    while(1){
        stateServer->computerVision->sendToConnection("ask_distance");
        stateServer->computerVision->receiveFromConnection();

        stateServer->last_receival_time = getCurrentSecond();

        printf("Received distance from computer vision client: %s\n", stateServer->computerVision->buffer);

        distance = strtol(stateServer->computerVision->buffer, &eptr, 10);

        if(errno != EINVAL){
            if(distance > 30){
                stateServer->currentState = StateMachine::WALKING;
            }else if(distance >= 0 && distance <= 30){
                stateServer->currentState = StateMachine::GRABBING;
            }else if(distance < 0){
                //This is where it gets with a timeout
                stateServer->currentState = StateMachine::IDLE;
            }
        }

        usleep(100*1000); //Sleep for 100ms
    }
}

void *motionManagerThread(void* thread_arg){
    int amountMsSinceLastData = 0;

    auto stateServer = (StateServer*)thread_arg;

    printf("Waiting for connection from the motion manager.\n");
    stateServer->motionManager->waitForConnection();
    printf("Motion manager connected!\n");

    while(1){
        if(getCurrentSecond() - stateServer->last_receival_time > 3){
            printf("Amount since last data is 3 seconds or more!\n");
            stateServer->currentState = StateMachine::IDLE;
        }

        stateServer->motionManager->receiveFromConnection();

        if(strncmp(stateServer->motionManager->buffer, "ask_state", 9) == 0){
            stateServer->motionManager->sendToConnection(stateToString(stateServer->currentState));
        }
        usleep(100*1000); //Sleep for 100ms
    }
}

StateServer::StateServer() {
    this->computerVision = new ConnectionServer(8080);
    this->motionManager = new ConnectionServer(8081);

    this->currentState = StateMachine::IDLE;

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



