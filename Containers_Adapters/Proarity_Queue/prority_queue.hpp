#ifndef PIQ_H
#define PIQ_H

#include <iostream>
#include <vector>




template <class T, class Comp = std::less<T>>
class Proarity_queue {

public:
    Proarity_queue() = default;
    Proarity_queue(const std::vector<T>& vec);
    Proarity_queue(const Comp& comp);

public:
    const T& top() const;

    void push(const T& val);
    void pop();
    bool empty() const;
    size_t size() const; 
    void display() const;

private:
    void heapify(size_t index);
    void buildHeap();


private:
    Comp compar;
    std::vector<T> m_arr;
};




#include "prority_queue.tpp"


#endif //PIQ_H