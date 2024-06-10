#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <vector>
#include <stdexcept>
#include <utility>
#include <iterator>

template<typename T>
class Queue {
private:
    std::vector<T> data;
    size_t frontIndex;

public:
    Queue();
    explicit Queue(size_t initialCapacity);
    ~Queue() = default;
    Queue& operator=(const Queue& other);

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    bool empty() const;
    size_t size() const;

    void enqueue(const T& value);
    void push(const T& value);
    void push_range(const T* first, const T* last);
    void dequeue();
    void pop();
    void swap(Queue& other);

    void shrink_to_fit();
};

template<typename T>
bool operator==(const Queue<T>& lhs, const Queue<T>& rhs);
template<typename T>
bool operator!=(const Queue<T>& lhs, const Queue<T>& rhs);
template<typename T>
bool operator<(const Queue<T>& lhs, const Queue<T>& rhs);
template<typename T>
bool operator<=(const Queue<T>& lhs, const Queue<T>& rhs);
template<typename T>
bool operator>(const Queue<T>& lhs, const Queue<T>& rhs);
template<typename T>
bool operator>=(const Queue<T>& lhs, const Queue<T>& rhs);

#include "Queue.tpp"

#endif // QUEUE_HPP
