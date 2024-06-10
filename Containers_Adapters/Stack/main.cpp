#include <iostream>
#include "Stack.hpp"

int main() {
    Stack<int> stack(10); // Reserve space for 10 elements initially

    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << "Stack size: " << stack.size() << std::endl;
    std::cout << "Top element: " << stack.top() << std::endl;

    stack.pop();
    std::cout << "Top element after pop: " << stack.top() << std::endl;

    stack.pop();
    stack.pop();
    if (stack.empty()) {
        std::cout << "Stack is empty." << std::endl;
    }

    return 0;
}
