#ifndef SOCKET_COMMUNICATION_H
#define SOCKET_COMMUNICATION_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

class SocketCommunication{
private:
    int socket_fd;
public:
    char buffer[1024];

    void receiveFromServer();
    void sendToServer(const char * string);

    explicit SocketCommunication(int);
    virtual ~SocketCommunication();
};

#endif //SOCKET_COMMUNICATION_H
