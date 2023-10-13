#pragma once

#include "order.hpp"
#include "types.hpp"
#include <iostream>

class SellOrder: public Order {
    OrderType type;
public:
    SellOrder(double price, double quantity, long long time): Order(price, quantity, time), type(OrderType::SELL) {}

    void display();
};