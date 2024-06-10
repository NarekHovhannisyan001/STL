#ifndef STACK_TPP
#define STACK_TPP

template<typename T>
Stack<T>::Stack() = default;

template<typename T>
Stack<T>::Stack(size_t initialCapacity) {
    data.reserve(initialCapacity);
}

template<typename T>
void Stack<T>::push(const T& value) {
    data.push_back(value);
}

template<typename T>
void Stack<T>::pop() {
    if (data.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    data.pop_back();
}

template<typename T>
T& Stack<T>::top() {
    if (data.empty()) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return data.back();
}

template<typename T>
bool Stack<T>::empty() const {
    return data.empty();
}

template<typename T>
size_t Stack<T>::size() const {
    return data.size();
}

template<typename T>
void Stack<T>::shrink_to_fit() {
    data.shrink_to_fit();
}

#endif // STACK_TPP
