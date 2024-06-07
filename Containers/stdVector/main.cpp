#include <iostream>
#include "Vector.hpp"

int main() {
    // Create a Vector of integers
    Vector<int> intVector;

    // Add elements to the Vector
    for (int i = 1; i <= 5; ++i) {
        intVector.push_back(i * 10);
    }

    // Print the Vector using the print method
    std::cout << "Vector elements: ";
    intVector.print();
    std::cout << std::endl;

    // Access elements using the subscript operator
    std::cout << "Element at index 2: " << intVector[2] << std::endl;

    // // Modify an element using the subscript operator
    intVector[3] = 100;

    // // Print the modified Vector
    std::cout << "Modified Vector elements: ";
    intVector.print();
    std::cout << std::endl;

    // // Use iterators to traverse the Vector
    std::cout << "Vector elements using iterators: ";
    auto it = intVector.begin();
    for (auto it = intVector.begin(); it != intVector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // // Resize the Vector
    intVector.resize(8);

    // Print the resized Vector
    std::cout << "Resized Vector elements: ";
    intVector.print();
    std::cout << std::endl;

    // Clear the Vector
    intVector.clear();

    // Check if the Vector is empty
    std::cout << "Is the Vector empty? " << (intVector.empty() ? "Yes" : "No") << std::endl;

    return 0;
}
