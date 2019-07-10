//
// Created by erwin on 9-7-19.
//

#include "includes/ConnectionServer.h"

ConnectionServer::ConnectionServer(int port){
    int opt = 1;

    this->addr_len = sizeof(this->address);

    // Creating socket file descriptor
    if ((this->socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("Socket creation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port specified in the constructor arguments
    if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        printf("Setting socket options failed!\n");
        exit(EXIT_FAILURE);
    }
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr =INADDR_ANY;
    this->address.sin_port = htons((uint16_t)port);

    // Forcefully attaching socket to the port defined
    if (bind(this->socket_fd, (struct sockaddr *)&this->address,sizeof(address))<0)
    {
        perror("Binding socket to port failed!\n");
        exit(EXIT_FAILURE);
    }
    if (listen(this->socket_fd, 3) < 0)
    {
        perror("Listening on socket failed!\n");
        exit(EXIT_FAILURE);
    }
}

void ConnectionServer::waitForClient(){
    if ((this->client_fd = accept(this->socket_fd, (struct sockaddr *)&address,(socklen_t*)&this->addr_len))<0)
    {
        perror("Accepting the client failed!\n");
        exit(EXIT_FAILURE);
    }
}

void ConnectionServer::receiveFromClient(){
    memset(this->buffer, 0, 1024);
    read(this->client_fd, this->buffer, 1024);
}

void ConnectionServer::sendToClient(const char * string){
    send(this->client_fd , string, strlen(string), 0);
}

void ConnectionServer::closeConnection(){
    close(this->client_fd);
}

ConnectionServer::~ConnectionServer() {
    this->closeConnection();
    close(this->socket_fd);
}
