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
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port specified in the constructor arguments
    if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr =INADDR_ANY;
    this->address.sin_port = htons(port);

    // Forcefully attaching socket to the port defined
    if (bind(this->socket_fd, (struct sockaddr *)&this->address,sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(this->socket_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

void ConnectionServer::waitForConnection(){
    if ((this->current_conn_fd = accept(this->socket_fd, (struct sockaddr *)&address,(socklen_t*)&this->addr_len))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
}

void ConnectionServer::receiveFromConnection(){
    memset(this->buffer, 0, 1024);
    read(this->current_conn_fd, this->buffer, 1024);
}

void ConnectionServer::sendToConnection(const char * string){
    send(this->current_conn_fd , string, strlen(string), 0);
}

void ConnectionServer::closeConnection(){
    close(this->current_conn_fd);
}

ConnectionServer::~ConnectionServer() {
    close(this->socket_fd);
}
