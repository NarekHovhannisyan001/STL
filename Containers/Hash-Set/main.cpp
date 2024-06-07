#include <iostream>
#include "hashSet.hpp"


int main() {
    MySet<int> set;
    set.insert(30);
    set.insert(40);
    set.insert(50);
    set.insert(41);
    set.insert(51);
    std::cout << set.getLF();
    set.insert(42);
    set.insert(52);
    set.insert(60);
    std::cout << set.getLF();
}