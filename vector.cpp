#include <iostream>
template<typename T>
class vector {
private:
    int capacity;
    T* arr;
    int size;
    
    void resize() {
        T* buf = new T[capacity];
        memcpy(arr, capacity, buf);
        delete[] arr;
        capacity *= 2;
        arr = new T[capacity];
        memcpy(buf, capacity, arr);
        delete[] buf;
    }
public:
    using value_type = T;
    using Iterator = iterator<vector<T>>;
    vector(int capacity) : capacity(capacity) {
        arr = new T[capacity];
        size = 0;
    }
    vector(const vector<T>& vec) {
        capacity = vec.capacity();
        size = vec.size();
        arr = new T[capacity];
        //deep copy
        memcpy(vec.arr, size, arr);
    }
    vector<T>& operator=(const vector<T>& vec) {
        if (vec.size() <= capacity) {
            memcpy(vec.arr, vec.size(), arr);
            size = vec.size();
            return *this;
        }
        delete[] arr;
        arr = new T[vec.size()*2];
        capacity = vec.size()*2;
        size = vec.size();
        memcpy(vec.arr, size, arr);
        return *this;
    }
    vector(vector<T>&& vec) {
        size = vec.size;
        capacity = vec.capacity;
        arr = vec.arr;
        vec.size = 0;
        vec.capacity = 0;
        vec.arr = nullptr;
    }
    vector<T>& operator=(vector<T>&& vec) {
        delete[] arr; 
        size = vec.size;
        capacity = vec.capacity;
        arr = vec.arr;
        vec.arr = nullptr;
        vec,size = 0;
        vec.capacity = 0;
        return *this;
    }
    void push_back(const T& elem) {
        arr[size++] = elem;
        if (size >= capacity) {
            resize();
        }
    }
    T operator[](int index) {
        return arr[index];
    }
    T& back() {
        return arr[size-1];
    }
    T& front() {
        return arr[0];
    }
    int size() {
        return size;
    }
    int capacity() {
        return capacity;
    }
    ~vector() {
        delete[] arr;
        capacity = 0;
        size = 0;
    }
    Iterator begin() {
        return Iterator(arr);
    }
    Iterator end() {
        return Iterator(arr+size);
    }
};

template<class vector>
class iterator {
private:
    using T = vector::value_type;
    using Ptr = T*;
    using Ref = T&;
    Ptr m_Ptr;
public:
    iterator(Ptr ptr) : m_Ptr(ptr) {}
    iterator& operator++() {
        m_Ptr++;
        return *this;
    }
    iterator& operator--() {
        m_Ptr--;
        return *this;
    }
    Ref operator[](int index) {
        return *(m_Ptr + index);
    }
    Ptr operator->() {
        return m_Ptr;
    }
    Ref operator*() {
        return *m_Ptr;
    }
    bool operator==(const iterator& other) const {
        return m_Ptr == other.m_Ptr;
    }
}
