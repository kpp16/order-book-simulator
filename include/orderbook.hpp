#pragma once

#include <string>
#include <queue>
#include <vector>
#include <nlohmann/json.hpp>
#include <map>
#include <variant>

#include "order.hpp"
#include "buy.hpp"
#include "sell.hpp"

using std::string;
using std::priority_queue;
using std::vector;
using json = nlohmann::json;
using std::map;
using std::variant;

struct BuyOrderComparator {
    bool operator()(const BuyOrder& o1, const BuyOrder& o2) {
        return o1.price < o2.price; // Sort buy orders by increasing quantity
    }
};

struct SellOrderComparator {
    bool operator()(const SellOrder& o1, const SellOrder& o2) {
        return o1.price > o2.price; // Sort sell orders by decreasing quantity
    }
};

class OrderBook {
public:
    priority_queue<BuyOrder, vector<BuyOrder>, BuyOrderComparator> buyOrders;
    priority_queue<SellOrder, vector<SellOrder>, SellOrderComparator> sellOrders;
    
    string tickerName;

    OrderBook(string &tickerName): tickerName(tickerName) {
    }

    json add_order(json &order);

};