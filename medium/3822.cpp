struct Order {
    int orderId;
    bool isBuy;
    int price;
    bool active = false;
};

class OrderManagementSystem {
    std::map<int, vector<int>> buy_levels, sell_levels; // price level, qty
    std::vector<Order> orders;

    inline vector<int>& getLevel(bool isBuy, int price) {
        return isBuy ? buy_levels[price] : sell_levels[price];
    }

    inline void invalidateLevel(Order& o) {
        auto& level = getLevel(o.isBuy, o.price);
        level.erase(find(level.begin(), level.end(), o.orderId));
    }

public:
    OrderManagementSystem() {
        orders.resize(2e3 + 1);
    }

    void addOrder(int orderId, string orderType, int price) {
        bool isBuy = orderType == "buy";
        orders[orderId] = {orderId, orderType == "buy", price, true};
        auto& level = getLevel(isBuy, price);
        level.push_back(orderId);
    }

    void modifyOrder(int orderId, int newPrice) {
        Order& o = orders[orderId];
        if (o.price != newPrice) {
            invalidateLevel(o);
            getLevel(o.isBuy, newPrice).push_back(orderId);
            o.price = newPrice;
        }
    }

    void cancelOrder(int orderId) {
        Order& o = orders[orderId];
        o.active = false;
        invalidateLevel(o);
    }

    vector<int> getOrdersAtPrice(string orderType, int price) {
        return getLevel(orderType == "buy", price);
    }
};

/**
 * Your OrderManagementSystem object will be instantiated and called as such:
 * OrderManagementSystem* obj = new OrderManagementSystem();
 * obj->addOrder(orderId,orderType,price);
 * obj->modifyOrder(orderId,newPrice);
 * obj->cancelOrder(orderId);
 * vector<int> param_4 = obj->getOrdersAtPrice(orderType,price);
 */
