#include "../include/orderBooks.hpp"

void OrderBooks::addOrderBook (OrderBook *orderBook) {
    std::string name = orderBook->tickerName;
    orderBooks[name] = orderBook;
}

OrderBook* OrderBooks::getOrderBook(std::string &ticker) {
    return orderBooks[ticker];
}