#include <iostream>
#include <vector>
#include <memory>
#include <string>


struct Order {
    std::string type;
    int qty;
    int price;
};
void mergeInPlace(int start, int mid, int end, auto comp, std::vector<Order>& orders) {
    int i = start, j = mid+1;
    while (i <= mid && j <= end) {
        if (comp(orders[i], orders[j])) {
            i++;
        }
        else {
            orders.insert(orders.begin()+i, orders[j++]);
            i++;
        }
    }
}
void merge(int start, int mid, int end, auto comp, std::vector<Order>& orders) {
    std::vector<Order> temp;
    int i = start, j = mid+1;
    while (i <= mid && j <= end) {
        if (comp(orders[i], orders[j])) {
            temp.push_back(orders[i++]);
        }
        else {
            temp.push_back(orders[j++]);
        }
    }
    while (i <= mid) temp.push_back(orders[i++]);
    while (j <= end) temp.push_back(orders[j++]);
    for (int k = start; k <= end; k++) {
        orders[k] = temp[k-start];
    }
}
void mergeSort(int start, int end, auto comp, std::vector<Order>& orders) {
    if (start >= end) return;
    int mid = (start+end) / 2;
    mergeSort(start, mid, comp, orders);
    mergeSort(mid+1, end, comp, orders);
    mergeInPlace(start, mid, end, comp, orders);
}
int main() {
    // Write C++ code here
    auto comp = [](const Order& lhs, const Order& rhs) {
        if (rhs.type == "BUY" && lhs.type == "BUY") {
            return lhs.price < rhs.price;
        }
        else if (lhs.type == "BUY" && rhs.type == "SELL") {
            return true;
        }
        else if (rhs.type == "BUY" && lhs.type == "SELL") {
            return false;
        }
        else {
            return lhs.qty > rhs.qty;
        }
    };
    std::vector<Order> orders;
    
    orders.push_back(Order{"BUY", 12, 200});
    orders.push_back(Order{"SELL", 32, 1200});
    orders.push_back(Order{"BUY", 23, 293});
    orders.push_back(Order{"SELL", 23, 300});
    
    mergeSort(0, 3, comp, orders);
    for (int i = 0; i < 4; i++) {
        std::cout << "TYPE: " << orders[i].type << " QTY: " << orders[i].qty << " PRICE: " << orders[i].price << " ";
        
    }
    std::cout << std::endl;
    return 0;
}
