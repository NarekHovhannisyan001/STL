#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
#include <stdexcept>

template<typename T>
class Stack {
public:
    Stack();
    explicit Stack(size_t initialCapacity);

    void push(const T& value);
    void pop();
    T& top();
    bool empty() const;
    size_t size() const;
    void shrink_to_fit();
    
private:
    std::vector<T> data;
};

#include "Stack.tpp"

#endif // STACK_HPP
