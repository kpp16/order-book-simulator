#pragma once

#include "order.hpp"
#include "types.hpp"
#include <iostream>

class BuyOrder: public Order {
    OrderType type;
public:
    BuyOrder(double price, double quantity, long long time): Order(price, quantity, time), type(OrderType::BUY) {}

    void display();

};