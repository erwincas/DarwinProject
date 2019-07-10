/*
 * main.cpp
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#include "DetectionManager.h"
#include <unistd.h>
#include <pthread.h>


void *detectionManagerThread(void *thread_args){
    DetectionManager manager;
    while(true)
    {
        manager.handle();
        manager.nextState();
    }
}

int main()
{
    pthread_attr_t threadAttr;
    pthread_t dmThread;

    pthread_attr_init(&threadAttr);

    lowPriority.sched_priority = 70;

    pthread_attr_setschedparam(&threadAttr, &lowPriority);
    pthread_attr_setschedpolicy(&threadAttr, SCHED_FIFO);

    pthread_create(&dmThread, &threadAttr, detectionManagerThread, 0);

    pthread_join(dmThread, NULL);

	return 0;
}

