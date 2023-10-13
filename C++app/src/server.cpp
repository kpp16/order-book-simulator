#include "../include/server.hpp"
#include "../include/RESTApi.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;


void Server::accept_connections() {
    if (listen(serverSocket, 5) < 0) { // Listen for up to 5 connections
        throw ServerException("Error listening on socket");
    }

    std::cout << "Listening on port " << port << std::endl;

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
        throw ServerException("Error accepting connections");
    }

    std::cout << "Accepted connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

    char buffer[1024];
    int bytesRead;

    while (true) {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead < 0) {
            std::cerr << "Error reading from socket" << std::endl;
            break;
        } else if (bytesRead == 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        }

        // Process the received data (you can replace this with your logic)
        std::string receivedData(buffer, bytesRead);
        std::cout << "Received: " << receivedData << std::endl;

        try {
            json sendData = json::parse(receivedData);

            if (sendData["type"] == "order") {
                std::string ticker = sendData["ticker"];
                OrderBook *orderBook = orderBooks.getOrderBook(ticker);

                json ret = orderBook->add_order(sendData);
                auto orderID = ret["id"];

                std::cout << orderID << "\n";


                std::string retStr = ret.dump();


                std::string suffix_url = "/addorder";


                std::future<std::string> response_future = restAPI->PerformAsyncPostRequest(suffix_url, 
                                                                                            retStr);
                std::string resp = response_future.get();

                std::cout << "Resp: " << resp << "\n";

                ret = json::parse(resp);

                json clientSend;
                clientSend["id"] = orderID;
                clientSend["message"] = ret["message"];

                std::string returnString = clientSend.dump();
                returnString += "\n";


                send(clientSocket, returnString.c_str(), returnString.size(), 0);
                
            }

        } catch (std::exception e) {
            std::string err = "Error processing input\n";
            send(clientSocket, err.c_str(), err.size(), 0);
            std::cout << e.what() << "\n";
        }
    }

    // Close sockets
    close(clientSocket);
    close(serverSocket);      
}