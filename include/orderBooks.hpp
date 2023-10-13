#pragma once

#include "orderbook.hpp"
#include <map>
#include <string>

using std::map;

class OrderBooks {
    map<std::string, OrderBook*> orderBooks;

public:
    void addOrderBook(OrderBook *orderBook);
    OrderBook* getOrderBook(std::string &ticker);
};