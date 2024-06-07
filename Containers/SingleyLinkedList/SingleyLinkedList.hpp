#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
class List
{

public:
    List();
    ~List();

public:
    bool is_empty() const;
    void print() const;
    void push_front(const T &value);
    void pop_front();
    void push_back(const T &val);
    void pop_back();
    void erase(size_t pos);
    void insert(size_t position, const T &value);
    bool find(const T &val) const;
    void clear();
    T &front();
    const T &front() const;
    T &back();
    const T &back() const;
    T &operator[](size_t index);
    const T &operator[](size_t index) const;

private:
    struct Node
    {
        T data;
        Node *next;

        Node(const T &obj);
    };

    Node *m_head;

public:
    class iterator
    {
    private:
        Node *current;

    public:
        iterator(Node *node);

        T &operator*() const;
        iterator &operator++();
        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
    };

    iterator begin() const;
    iterator end() const;
};

#include "list.tpp"

#endif // LIST_H
