#include "MotionClass.h"
#include "SocketCommunication.h"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *motionManagerThread(void *thread_args){
    MotionClass motionClass;
    SocketCommunication socket(8081);

	motionClass.walkForward();

	while(1){
		socket.receiveFromServer();

		if(strncmp(socket.buffer, "WALKING", 7) == 0){
			printf("NOW STARTING WALKING \n");
		}else if(socket.buffer, "GRABBING", 8) == 0){
			printf("NOW STARTING GRABBING \n");
		}else if(socket.buffer, "IDLE", 4) == 0){
			printf("NOW IDLING \n");
		}
	}
}

int main(void) {
	pthread_attr_t threadAttr;
    pthread_t mmThread;

    pthread_attr_init(&threadAttr);

    lowPriority.sched_priority = 60;

    pthread_attr_setschedparam(&threadAttr, &lowPriority);
    pthread_attr_setschedpolicy(&threadAttr, SCHED_FIFO);

    pthread_create(&mmThread, &threadAttr, motionManagerThread, 0);

	pthread_join(mmThread, NULL);

	return 0;
}
