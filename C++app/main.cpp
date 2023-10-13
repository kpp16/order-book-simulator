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

    const char* url_arg = "CLUSTER_URL";
    const char* value = std::getenv(url_arg);

    if (value != nullptr) {
        std::string base_url(value);

        RESTApi *restAPI = new RESTApi(base_url);

        Server server(8080, orderBooks, restAPI);
        server.accept_connections();
    }

    std::cerr << "Cannot connect to the cluster URL\n";

    return 0;    
}