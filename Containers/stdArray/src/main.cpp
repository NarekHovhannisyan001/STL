#include <iostream>
#include "../headers/std::array.hpp"

int main() {
    // Test Array<int>
    Array<int, 5> intArray;
    intArray.fill(10);

    std::cout << "intArray elements: ";
    for (const auto& elem : intArray) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    intArray[2] = 20;
    std::cout << "intArray[2]: " << intArray[2] << std::endl;

    // Test Array<bool>
    Array<bool, 10> boolArray;
    boolArray.fill(true);

    std::cout << "boolArray elements: ";
    for (const auto& elem : boolArray) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    boolArray[3] = false;
    std::cout << "boolArray[3]: " << boolArray[3] << std::endl;

    return 0;
}
