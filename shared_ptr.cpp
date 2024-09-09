#include <iostream>

class RefCounter {
    int counter;
public:
    RefCounter()  {counter = 1;}
    RefCounter& operator--() {
        --counter;
        return *this;
    }
    RefCounter& operator++() {
        ++counter;
        std::cout << counter << std::endl;
        return *this;
    }
    void inc() {
        counter++;
    }
    void dec() {
        counter--;
    }
    int get() {
        return counter;
    }
};
template<typename T>
class shared_ptr {
private:
    T* data;
    RefCounter* counter;
public:
    shared_ptr(T* data) : data(data) {
        counter = new RefCounter();
    }
    shared_ptr(const shared_ptr& ptr) {
        std::cout << "Copy constructor" << std::endl;
        data = ptr.data;
        counter = ptr.counter;
        counter->inc();
    }
    shared_ptr& operator=(const shared_ptr& ptr) {
        std::cout << "Copy assignment" << std::endl;
        if (ptr == *this) return *this;
        counter->dec();
        if (counter->get() == 0) {
            delete data;
            delete counter;
        }
        data = ptr.data;
        counter = ptr.counter;
        counter->inc();
        return *this;
    }
    shared_ptr(shared_ptr&& ptr) = delete;
    shared_ptr& operator=(shared_ptr&& ptr) = delete;
    ~shared_ptr() {
        std::cout << "Destorying" << std::endl;
        counter->dec();
        if (counter->get() == 0) {
            std::cout << "Deleting";
            delete data;
            delete counter;
        }
    }
    T* operator->() {
        return data;
    }
    T& operator*() {
        return *data;
    }
    T* get() {
        return data;
    }
};
int main() {
    int* point;
{
    shared_ptr<int> firstPtr(new int {10});
    {
        shared_ptr<int> secondPtr(firstPtr);
        std::cout << *secondPtr << std::endl;
    }
    std::cout << *firstPtr << std::endl;
    //std::cout << *movedPtr << std::endl;
    std::cout << "Try programiz.pro" << std::endl;
    point = firstPtr.get();
}
    // Write C++ code here
    std::cout << *point << std::endl;
    

    return 0;
}
