//
// Created by erwin on 9-7-19.
//

#ifndef STATESERVER_CONNECTIONSERVER_H
#define STATESERVER_CONNECTIONSERVER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// This is a connection server with support for one connection at a time. Which was tested as successful.
class ConnectionServer{
private:
    int socket_fd, current_conn_fd, addr_len;
    struct sockaddr_in address;
public:
    char buffer[1024];

    explicit ConnectionServer(int);
    virtual ~ConnectionServer();
    void waitForConnection();
    void receiveFromConnection();
    void sendToConnection(const char *);
    void closeConnection();
};


#endif //STATESERVER_CONNECTIONSERVER_H
