#include <iostream>
#include <vector>

template<typename T>
class deque {
private:
    int blocksize;
    std::vector<pair<T*, int*>> data;
public:
    deque() {
        blocksize = 8;
        
        data.push_back(new)
    }
    void push_back(const T& elem) {
        T* ptr = data.back().first;
        int* size = data.back().second;
        if (*size < blocksize) {
            ptr[*size++] = elem;
            return;
        }
        T* newBlk = new T[blocksize];
        newBlk[0] = elem;
        int* size = new int{1};
        data.push_back({newBlk, size});
    }
    void push_front(const T& elem) {
        T* ptr = data.front().first;
        int* size = data.front().second;
        if (*size < blocksize) {
            ptr[blkSize-*size-1] = elem;
            *size++;
            return;
        }
        T* newBlk = new T[blocksize];
        newBlk[0] = elem;
        int* size = new int{1};
        data.insert(data.begin(), {newBlk, size});
    }
    void pop_back() {
        T* ptr = data.back().first;
        int* size = data.back().second;
        ptr[--*size] = 0;
        if (*size == 0) {
            delete[] ptr;
            delete size;
            data.pop_back();
        }
    }
    void pop_front() {
        T* ptr = data.front().first;
        int* size = data.front().second;
        ptr[blocksize-*size] = 0;
        *size--;
        if (*size == 0) {
            delete[] ptr;
            delete size;
            data.erase(data.begin());
        }
    }
    T& front() {
        T* ptr = data.front().first;
        int* size = data.front().second;
        return ptr[blocksize-*size];
    }
    T& back() {
        T* ptr = data.back().first;
        int* size = data.back().second;
        return ptr[*size-1];
    }
};

int main() {
    // Write C++ code here
    std::cout << "Try programiz.pro";

    return 0;
}
