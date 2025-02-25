#include <iostream>
#include "Vector.hpp"

int main()
{
    Vector<int> intVector;

    for (int i = 1; i <= 5; ++i)
    {
        intVector.push_back(i * 10);
    }
    std::cout << "Vector elements: ";
    print(intVector);
    std::cout << std::endl;

    // Access elements using the subscript operator
    std::cout << "Element at index 2: " << intVector[2] << std::endl;

    // // Modify an element using the subscript operator
    intVector[3] = 100;

    // // Print the modified Vector
    std::cout << "Modified Vector elements: ";
    print(intVector);
    std::cout << std::endl;

    // // Use iterators to traverse the Vector
    std::cout << "Vector elements using iterators: ";
    auto it = intVector.begin();
    for (auto it = intVector.begin(); it != intVector.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // // Resize the Vector
    intVector.resize(8);

    // Print the resized Vector
    std::cout << "Resized Vector elements: ";
    print(intVector);
    std::cout << std::endl;

    // Clear the Vector
    intVector.clear();

    // Check if the Vector is empty
    std::cout << "Is the Vector empty? " << (intVector.empty() ? "Yes" : "No") << std::endl;

    // Matrix case
    Vector<Vector<int>> mat;
    mat.emplace_back();
    mat[0].emplace_back();
    mat[0][0] = 2;
    std::cout << "Matrix's first element " << mat[0][0] << std::endl;

    return 0;
}
