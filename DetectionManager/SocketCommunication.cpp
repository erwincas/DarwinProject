//
// Created by erwin on 10-7-19.
//

#include "SocketCommunication.h"

SocketCommunication::SocketCommunication(int port) {
    struct sockaddr_in serv_addr;

    if ((this->socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(this->socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
}

void SocketCommunication::receiveFromServer(){
    memset(this->buffer, 0, 1024);
    read(this->socket_fd, this->buffer, 1024);
}

void SocketCommunication::sendToServer(const char *string){
    this->receiveFromServer();

    if(strncmp(this->buffer, "ask_distance", 12) == 0){
        send(this->socket_fd , string , strlen(string) , 0);
    }
}

SocketCommunication::~SocketCommunication() {
    close(this->socket_fd);
}
