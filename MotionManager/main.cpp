#include "WalkingStateManager.h"
#include "SocketCommunication.h"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct arg_struct {
    SocketCommunication *socket;
    WalkingStateManager *walkingStateManager;
}args;

void *motionManagerThread(void *thread_args){
	printf("\n--------------------------\nmotion manager thread \n--------------------------\n");
	struct arg_struct *mm_args = (arg_struct *) thread_args;

	
	char str[1024];
	
	while(1){
		mm_args->socket->receiveFromServer();

			strcpy(str, mm_args->socket->buffer);

			mm_args->walkingStateManager->walkFlag = 0;
			if(strncmp(mm_args->socket->buffer, "WALKING", 7) == 0){
				printf("NOW STARTING WALKING \n");
				mm_args->walkingStateManager->walkFlag = 1;
				mm_args->walkingStateManager->nextState();

			}else if(strncmp(mm_args->socket->buffer, "GRABBING", 8) == 0){
				printf("NOW STARTING GRABBING \n");
				mm_args->walkingStateManager->nextState();

			}else if(strncmp(mm_args->socket->buffer, "IDLE", 4) == 0){
				printf("NOW IDLING \n");
				mm_args->walkingStateManager->prevState();
				
			}
		
		mm_args->walkingStateManager->handle();
	}
}

int main(void) {

	printf("\n--------------------------\n starting motionclass \n--------------------------\n");
	args.walkingStateManager = new WalkingStateManager;

	args.socket = new SocketCommunication(8081);
	
    pthread_t mmThread;
	printf("\n--------------------------\nStart motion thread \n--------------------------\n");
    pthread_create(&mmThread, NULL, motionManagerThread, &args);
	
	pthread_join(mmThread, NULL);
	printf("\n--------------------------\nmotion thread stopped \n--------------------------\n");

	return 0;
}


