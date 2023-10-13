#pragma once

#include <random>

class Order {
    int generateRandomID() {
        std::random_device rd;  // A non-deterministic random number generator
        std::mt19937 mt(rd()); // Mersenne Twister pseudo-random number generator
        std::uniform_int_distribution<long long> dist(0, 1e9); // Range for random IDs

        return dist(mt); // Generate and return a random ID between 1000 and 9999
    }
public:
    Order(double price, double quantity, long long time) : id(generateRandomID()), price(price), quantity(quantity), time(time) {}

    double price;
    double quantity;
    long long time;
    long long id;
};