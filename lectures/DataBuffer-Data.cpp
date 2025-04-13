#include <iostream>
#include <cstring>

int increment_counter() {
    static int counter = 0;
    return counter++;
}

struct Data {
public:
    int value;
    Data(int x = 42) : value(x) {}
    Data(const Data& data) {
        value = data.value;
    }
    ~Data() {
        // std::cout << "~Data() called " << std::endl;
        increment_counter();
    }
    Data& operator=(const Data& data) {
        value = data.value;

        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Data data) {
        os << data.value;
        return os;
    }
};

class DataBuffer {
    Data* addr;
    size_t size_buf;
    friend void std::swap(DataBuffer& a, DataBuffer& b);
public:
    DataBuffer(size_t size) {
        // std::cout << "called11!" << std::endl;
        size_buf = size;
        addr = new Data[size_buf];
    }
    DataBuffer(const DataBuffer& data_buf) = delete;
    const DataBuffer& operator=(const DataBuffer& data_buf) = delete;
    DataBuffer(DataBuffer&& data_buf) noexcept : addr(data_buf.addr), size_buf(data_buf.size_buf) {
        // std::cout << "Move constructor called!" << std::endl;
        data_buf.addr = nullptr;
        data_buf.size_buf = 0;
    }
    DataBuffer& operator=(DataBuffer&& data_buf) noexcept {
        // std::cout << "Move assignment operator called!" << std::endl;
        if (this != &data_buf) {
            delete[] addr;
            addr = data_buf.addr;
            size_buf = data_buf.size_buf;
            data_buf.addr = nullptr;
            data_buf.size_buf = 0;
        }
        return *this;
    }
    ~DataBuffer() {
        // std::cout << "called1!" << std::endl;
        delete[] addr;
    }
    size_t size() const {
        return size_buf;
    }
    Data& operator[](const size_t ind) {
        return addr[ind];
    }
    const Data& operator[](const size_t ind) const {
        return addr[ind];
    }
};

namespace std {
    template<>
    void swap<DataBuffer>(DataBuffer& a, DataBuffer& b) {
        std::swap(a.addr, b.addr);
        std::swap(a.size_buf, b.size_buf);
    }
}

void print_buffer(const DataBuffer& buffer) {
    for (size_t i = 0; i < buffer.size(); i++)
        std::cout << "buffer[" << i << "] == " << buffer[i] << std::endl;
}

int main() {
    {
        DataBuffer buffer_1{ 5 }, buffer_2{ 3 };

        std::cout << "buffer_1.size() == " << buffer_1.size() << std::endl;
        std::cout << "buffer_2.size() == " << buffer_2.size() << std::endl;

        for (size_t i = 0; i < buffer_2.size(); i++)
            buffer_2[i] = i + 1;

        std::cout << "buffer_1[0] == " << buffer_1[0].value << std::endl;
        std::cout << "buffer_2[0] == " << buffer_2[0].value << std::endl;

        std::swap(buffer_1, buffer_2);
        // DataBuffer buffer_copy = buffer_1; // forbidden!

        std::cout << "buffer_1.size() == " << buffer_1.size() << std::endl;
        std::cout << "buffer_2.size() == " << buffer_2.size() << std::endl;

        print_buffer(buffer_1);
    }
    std::cout << "~Data() called " << increment_counter() << " times" << std::endl;
    return 0;
}