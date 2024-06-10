#ifndef QUEUE_TPP
#define QUEUE_TPP

template<typename T>
Queue<T>::Queue() : frontIndex(0) {}

template<typename T>
Queue<T>::Queue(size_t initialCapacity) : frontIndex(0) {
    data.reserve(initialCapacity);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        data = other.data;
        frontIndex = other.frontIndex;
    }
    return *this;
}

template<typename T>
T& Queue<T>::front() {
    if (data.empty() || frontIndex == data.size()) {
        throw std::out_of_range("Queue<>::front(): empty queue");
    }
    return data[frontIndex];
}

template<typename T>
const T& Queue<T>::front() const {
    if (data.empty() || frontIndex == data.size()) {
        throw std::out_of_range("Queue<>::front(): empty queue");
    }
    return data[frontIndex];
}

template<typename T>
T& Queue<T>::back() {
    if (data.empty()) {
        throw std::out_of_range("Queue<>::back(): empty queue");
    }
    return data.back();
}

template<typename T>
const T& Queue<T>::back() const {
    if (data.empty()) {
        throw std::out_of_range("Queue<>::back(): empty queue");
    }
    return data.back();
}

template<typename T>
bool Queue<T>::empty() const {
    return frontIndex == data.size();
}

template<typename T>
size_t Queue<T>::size() const {
    return data.size() - frontIndex;
}

template<typename T>
void Queue<T>::enqueue(const T& value) {
    push(value);
}

template<typename T>
void Queue<T>::push(const T& value) {
    data.push_back(value);
}

template<typename T>
void Queue<T>::push_range(const T* first, const T* last) {
    data.insert(data.end(), first, last);
}


template<typename T>
void Queue<T>::dequeue() {
    pop();
}

template<typename T>
void Queue<T>::pop() {
    if (data.empty() || frontIndex == data.size()) {
        throw std::out_of_range("Queue<>::pop(): empty queue");
    }
    ++frontIndex;
    if (frontIndex == data.size()) {
        data.clear();
        frontIndex = 0;
    }
}

template<typename T>
void Queue<T>::swap(Queue<T>& other) {
    std::swap(data, other.data);
    std::swap(frontIndex, other.frontIndex);
}

template<typename T>
void Queue<T>::shrink_to_fit() {
    if (frontIndex > 0) {
        std::vector<T> newData(data.begin() + frontIndex, data.end());
        data.swap(newData);
        frontIndex = 0;
    }
    data.shrink_to_fit();
}

template<typename T>
bool operator==(const Queue<T>& lhs, const Queue<T>& rhs) {
    return lhs.size() == rhs.size() && std::equal(lhs.data.begin() + lhs.frontIndex, lhs.data.end(), rhs.data.begin() + rhs.frontIndex);
}

template<typename T>
bool operator!=(const Queue<T>& lhs, const Queue<T>& rhs) {
    return !(lhs == rhs);
}

template<typename T>
bool operator<(const Queue<T>& lhs, const Queue<T>& rhs) {
    return std::lexicographical_compare(lhs.data.begin() + lhs.frontIndex, lhs.data.end(), rhs.data.begin() + rhs.frontIndex, rhs.data.end());
}

template<typename T>
bool operator<=(const Queue<T>& lhs, const Queue<T>& rhs) {
    return !(rhs < lhs);
}

template<typename T>
bool operator>(const Queue<T>& lhs, const Queue<T>& rhs) {
    return rhs < lhs;
}

template<typename T>
bool operator>=(const Queue<T>& lhs, const Queue<T>& rhs) {
    return !(lhs < rhs);
}

#endif // QUEUE_TPP
