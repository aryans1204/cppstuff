#include <iostream>
#include <utility>
#include <vector>

template<typename T>
class unique_ptr {
public:
    T* data;
    unique_ptr(T* data) : data(data) {std::cout << "Constructor" << std::endl;}
    unique_ptr(const unique_ptr& ptr) = delete;
    unique_ptr& operator=(const unique_ptr& ptr) = delete;
    unique_ptr(unique_ptr&& ptr) noexcept {
        std::cout <<  "Moved" << std::endl;
        data = ptr.data;
        ptr.data = nullptr;
    }
    unique_ptr& operator=(unique_ptr&& ptr) noexcept {
        std::cout << "Move assigned" << std::endl;
        delete data;
        data = ptr.data;
        ptr.data = nullptr;
        return *this;
    }
    ~unique_ptr() {
        delete data;
    }
    T* operator->() {
        return data;
    }
    T& operator*() {
        return *data;
    }
};
int main() {
    // Write C++ code here
    unique_ptr<std::vector<int>> ptr(new std::vector<int>{10, 1, 2});
    //unique_ptr<int> newPtr(ptr);
    unique_ptr<std::vector<int>> latestPtr(std::move(ptr));
    unique_ptr<std::vector<int>> movedPtr(new std::vector<int>);
    movedPtr = std::move(latestPtr);
    //std::cout << *movedPtr << std::endl;
    std::cout << "Try programiz.pro";

    return 0;
}
