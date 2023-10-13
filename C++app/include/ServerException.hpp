#pragma once

#include <iostream>

class ServerException: public std::exception {
    char* message;

public:
    ServerException(char* message): message(message) {}
    char* what() {
        return message;
    }
};