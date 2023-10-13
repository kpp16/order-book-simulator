#pragma once

#define _BSD_SOURCE

#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

#include "ServerException.hpp"
#include "orderBooks.hpp"
#include "RESTApi.hpp"

class Server {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int port;

    OrderBooks orderBooks;
    RESTApi *restAPI;



public:

    Server(int port, OrderBooks &orderBooks, RESTApi *restAPI): orderBooks(orderBooks), port(port), restAPI(restAPI) {
    // Create socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            throw ServerException("Error creating socket");
        }

        // Bind the socket to a specific IP address and port
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port); // Port number (change as needed)
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            throw ServerException("Error binding socket");
        }        
    }

    void accept_connections();
};