#include "../include/orderbook.hpp"
#include "../include/buy.hpp"
#include "../include/sell.hpp"
#include "../include/order.hpp"

#include <string>

json OrderBook::add_order(json &order) {
    try {
        string action = order["action"];
        double price = order["price"];
        double quantity = order["quantity"];

        auto currentTimePoint = std::chrono::system_clock::now();
        auto durationInSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTimePoint.time_since_epoch());
        long long unixTime = durationInSeconds.count();
        long long id = -1;

        
        if (action == "buy") {
            BuyOrder buyOrder(price, quantity, unixTime);
            buyOrders.push(buyOrder);
            id = buyOrder.id;
        } else {
            SellOrder sellOrder(price, quantity, unixTime);
            sellOrders.push(sellOrder);
            id = sellOrder.id;
        }
        json data;
        
        data["id"] = std::to_string(id);
        data["price"] = price;
        data["quantity"] = quantity;
        data["time"] = unixTime;
        data["ticker"] = tickerName;
        data["status"] = "not filled";

        return data;        
    } catch (const std::exception &e) {
        json data;

        data["status"] = "failed";
        data["message"] = e.what();

        return data;
    }
}