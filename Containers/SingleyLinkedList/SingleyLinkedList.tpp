#ifndef LIST_T
#define LIST_T

#include "SinglyLinkedList.hpp"

template <typename T>
List<T>::Node::Node(const T &obj) : data(obj), next(nullptr) {}

template <typename T>
List<T>::List() : m_head(nullptr) {}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
void List<T>::push_front(const T &val)
{
    Node *tmp = new Node(val);
    if (m_head == nullptr)
    {
        m_head = tmp;
        return;
    }
    tmp->next = m_head;
    m_head = tmp;
}

template <typename T>
void List<T>::pop_front()
{
    if (m_head == nullptr)
    {
        throw std::runtime_error("Cannot pop from an empty list");
    }

    Node *tmp = m_head;
    m_head = m_head->next;
    delete tmp;
}

template <typename T>
void List<T>::print() const
{
    Node *current = m_head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
bool List<T>::is_empty() const
{
    return m_head == nullptr;
}

template <typename T>
void List<T>::clear()
{
    while (!is_empty())
    {
        pop_front();
    }
}

template <typename T>
void List<T>::push_back(const T &val)
{
    Node *new_node = new Node(val);
    if (m_head == nullptr)
    {
        m_head = new_node;
    }
    else
    {
        Node *current = m_head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

template <typename T>
bool List<T>::find(const T &val) const
{
    Node *current = m_head;
    while (current != nullptr)
    {
        if (current->data == val)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
T &List<T>::operator[](size_t index)
{
    Node *current = m_head;
    size_t i = 0;

    while (current != nullptr)
    {
        if (i == index)
        {
            return current->data;
        }

        current = current->next;
        ++i;
    }

    throw std::out_of_range("Index out of range");
}

template <typename T>
const T &List<T>::operator[](size_t index) const
{
    Node *current = m_head;
    size_t i = 0;

    while (current != nullptr)
    {
        if (i == index)
        {
            return current->data;
        }

        current = current->next;
        ++i;
    }

    throw std::out_of_range("Index out of range");
}

template <typename T>
void List<T>::pop_back()
{
    if (m_head == nullptr)
    {
        throw std::runtime_error("Cannot pop from an empty list");
    }

    if (m_head->next == nullptr)
    {
        delete m_head;
        m_head = nullptr;
        return;
    }

    Node *current = m_head;
    Node *previous = nullptr;

    while (current->next != nullptr)
    {
        previous = current;
        current = current->next;
    }

    delete current;
    previous->next = nullptr;
}

template <typename T>
void List<T>::insert(size_t position, const T &value)
{
    if (position == 0)
    {
        push_front(value);
        return;
    }

    Node *current = m_head;
    for (size_t i = 1; i < position && current != nullptr; ++i)
    {
        current = current->next;
    }

    if (current)
    {
        Node *newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
    }
    else
    {
        throw std::out_of_range("Invalid index: ");
    }
}

template <typename T>
void List<T>::erase(size_t position)
{
    if (position == 0)
    {
        pop_front();
        return;
    }

    Node *current = m_head;
    Node *previous = nullptr;
    for (size_t i = 0; i < position && current != nullptr; ++i)
    {
        previous = current;
        current = current->next;
    }

    if (previous && current)
    {
        previous->next = current->next;
        delete current;
    }
    else
    {
        throw std::out_of_range("Invalid index: ");
    }
}

template <class T>
T &List<T>::front()
{
    if (m_head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }
    return m_head->data;
}

template <class T>
const T &List<T>::front() const
{
    if (m_head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }
    return m_head->data;
}

template <class T>
T &List<T>::back()
{
    if (m_head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }
    Node *curr = m_head;
    while (curr->next)
    {
        curr = curr->next;
    }

    return curr->data;
}

template <class T>
const T &List<T>::back() const
{
    if (m_head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }
    List<T>::Node *curr = m_head;
    while (curr->next)
    {
        curr = curr->next;
    }

    return curr->data;
}

template <class T>
List<T>::iterator::iterator(Node *node) : current(node) {}

template <typename T>
T &List<T>::iterator::operator*() const
{
    return current->data;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator++()
{
    if (current != nullptr)
    {
        current = current->next;
    }
    return *this;
}

template <typename T>
bool List<T>::iterator::operator==(const iterator &other) const
{
    return current == other.current;
}

template <typename T>
bool List<T>::iterator::operator!=(const iterator &other) const
{
    return !(*this == other);
}

template <class T>
List<T>::iterator List<T>::begin() const
{
    return iterator(m_head);
}

template <class T>
List<T>::iterator List<T>::end() const
{
    return iterator(nullptr);
}

#endif // LIST-T
