#include <iostream>
#include <cstring>

class string {
    char* _data;
    int _size;
    
public:
    string(const char* data) {
        _size = strlen(data);
        _data = new char[_size+1];
        strcpy(_data, data);
    }
    string() {
        _data = new char;
        _size = 0;
    }
    string(const string& str) {
        std::cout << "Copy constructor called" << std::endl;
        _size = str._size;
        _data = new char[_size+1];
        strcpy(_data, str._data);
    }
    string& operator=(const string& str) {
        delete[] _data;
        _size = str._size;
        strcpy(_data, str._data);
        return *this;
    }
    string(string&& str) {
        _size = str._size;
        _data = str._data;
        str._data = nullptr;
        str._size = 0;
    }
    string& operator=(string&& str) {
        std::cout << "Move assignment called" << std::endl;
        delete[] _data;
         _size = str._size;
        _data = str._data;
        str._data = nullptr;
        str._size = 0;
        return *this;
    }
    bool operator==(const string& other) {
        return strcmp(other._data, _data) == 0;
    }
    int size() const {
        return _size;
    }
    char operator[](int index) {
        return _data[index];
    }
    string& operator+=(const string& str) {
        char* buf = new char[_size+1];
        strcpy(buf, _data);
        delete[] _data;
        _data = new char[_size+str._size+1];
        strncpy(_data, buf, _size);
        strcpy(_data+_size, str._data);
        _size += str._size+1;
        return *this;
    }
    char* get() const {
        return _data;
    }
    ~string() {
        delete[] _data;
        _size = 0;
    }
};
int main() {
    // Write C++ code here
    string newStr;
    {
        string str("Hello there");
        printf("%s\n", str.get());
        newStr = std::move(str);
    }
    printf("%s\n", newStr.get());
    newStr += " Aryan";
    printf("%s\n", newStr.get());
    
    
    return 0;
}
