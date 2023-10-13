#include <bits/stdc++.h>

#include "include/orderbook.hpp"
#include "include/server.hpp"
#include "include/orderBooks.hpp"
#include "include/RESTApi.hpp"


int main() {
    std::string tickerName = "AAPL";

    OrderBook *orderBook = new OrderBook(tickerName);

    OrderBooks orderBooks;
    orderBooks.addOrderBook(orderBook);

    std::string base_url = "http://192.168.49.2:31199";

    RESTApi *restAPI = new RESTApi(base_url);

    Server server(8080, orderBooks, restAPI);
    server.accept_connections();

    return 0;    
}