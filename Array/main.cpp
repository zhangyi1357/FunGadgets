#include <cstring>
#include <iostream>
#include <string>

#include "Array.h"

int main() {
    constexpr int size = 5;
    Array<int, size> data;

    static_assert(data.Size() < 10, "Size is too large");

    data[0] = 2;
    data[1] = 3;
    data[2] = 5;
    for (size_t i = 0; i < data.Size(); ++i)
        std::cout << data[i] << std::endl;
    std::cout << "-----------------" << std::endl;

    memset(data.Data(), 0, data.Size() * sizeof(int));
    for (size_t i = 0; i < data.Size(); ++i)
        std::cout << data[i] << std::endl;
    std::cout << "-----------------" << std::endl;

    Array<std::string, size> data2;
    data2[0] = "Cherno";
    data2[1] = "C++";
    for (size_t i = 0; i < data2.Size(); ++i)
        std::cout << data2[i] << std::endl;

    return 0;
}