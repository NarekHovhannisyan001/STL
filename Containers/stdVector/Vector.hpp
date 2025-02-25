#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <compare> 
#include <iterator>
#include <iostream>

template<typename T>
class Vector {
public:
    // Member types
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    // Iterators classes
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    // Ctors and dtor
    Vector();
    explicit Vector(size_type count);
    Vector(size_type count, const T& value);
    template<typename InputIt>
    Vector(InputIt first, InputIt last);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(std::initializer_list<T> init);
    ~Vector();

    // Assignment operators
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    Vector& operator=(std::initializer_list<T> ilist);

    // Element access
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    pointer data() noexcept;
    const_pointer data() const noexcept;

    // Iterators
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // Capacity
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void reserve(size_type new_cap);
    size_type capacity() const noexcept;
    void shrink_to_fit();

    // Modifiers
    void clear() noexcept;
    void assign(size_type count, const T& value);
    template<typename InputIt>
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> ilist);
    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);
    iterator insert(const_iterator pos, size_type count, const T& value);
    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    iterator insert(const_iterator pos, std::initializer_list<T> ilist);
    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    void push_back(const T& value);
    void push_back(T&& value);
    template<typename... Args>
    reference emplace_back(Args&&... args);
    void pop_back();
    void resize(size_type count);
    void resize(size_type count, const value_type& value);
    void swap(Vector& other) noexcept;

    // Additional methods
    template<typename... Args>
    iterator append_range(Args&&... args);


    // Comparison operators
    friend bool operator==(const Vector& lhs, const Vector& rhs) {
        if (lhs.count != rhs.count) return false;
        for (size_type i = 0; i < lhs.count; ++i) {
            if (!(lhs.elements[i] == rhs.elements[i])) return false;
        }
        return true;
    }

    friend std::strong_ordering operator<=>(const Vector& lhs, const Vector& rhs) {
        for (size_type i = 0; i < lhs.count && i < rhs.count; ++i) {
            if (auto cmp = lhs.elements[i] <=> rhs.elements[i]; cmp != 0) return cmp;
        }
        return lhs.count <=> rhs.count;
    }

private:
    //Helpers
    void reallocate(size_type new_cap);
    void destroy_elements();
private:
    pointer elements;
    size_type count;
    size_type capacity_;
};

// Iterators
template<typename T>
class Vector<T>::iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    iterator(pointer ptr) : ptr_(ptr) {}

    const_reference operator*() const { return *ptr_; }
    reference operator*() { return *ptr_; }
    pointer operator->() { return ptr_; }
    const_pointer operator->() const { return ptr_; }
    iterator& operator++() { ++ptr_; return *this; }
    iterator operator++(int) { iterator tmp = *this; ++ptr_; return tmp; }
    iterator& operator--() { --ptr_; return *this; }
    iterator operator--(int) { iterator tmp = *this; --ptr_; return tmp; }
    iterator& operator+=(difference_type offset) { ptr_ += offset; return *this; }
    iterator operator+(difference_type offset) const { return iterator(ptr_ + offset); }
    iterator& operator-=(difference_type offset) { ptr_ -= offset; return *this; }
    iterator operator-(difference_type offset) const { return iterator(ptr_ - offset); }
    difference_type operator-(const iterator& other) const { return ptr_ - other.ptr_; }
    reference operator[](difference_type offset) const { return *(ptr_ + offset); }
    bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
    bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }
    bool operator<=(const iterator& other) const { return ptr_ <= other.ptr_; }
    bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }
    bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }

private:
    pointer ptr_;
};


template<typename T>
class Vector<T>::const_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    const_iterator(pointer ptr) : ptr_(ptr) {}

    const_reference operator*() const { return *ptr_; }
    const_pointer operator->() const { return ptr_; }
    const_iterator& operator++() { ++ptr_; return *this; }
    const_iterator operator++(int) { const_iterator tmp = *this; ++ptr_; return tmp; }
    const_iterator& operator--() { --ptr_; return *this; }
    const_iterator operator--(int) { const_iterator tmp = *this; --ptr_; return tmp; }
    const_iterator& operator+=(difference_type offset) { ptr_ += offset; return *this; }
    const_iterator operator+(difference_type offset) const { return const_iterator(ptr_ + offset); }
    const_iterator& operator-=(difference_type offset) { ptr_ -= offset; return *this; }
    const_iterator operator-(difference_type offset) const { return const_iterator(ptr_ - offset); }
    difference_type operator-(const const_iterator& other) const { return ptr_ - other.ptr_; }
    reference operator[](difference_type offset) const { return *(ptr_ + offset); }
    bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }
    bool operator<(const const_iterator& other) const { return ptr_ < other.ptr_; }
    bool operator<=(const const_iterator& other) const { return ptr_ <= other.ptr_; }
    bool operator>(const const_iterator& other) const { return ptr_ > other.ptr_; }
    bool operator>=(const const_iterator& other) const { return ptr_ >= other.ptr_; }

private:
    pointer ptr_;
};

template<typename T>
class Vector<T>::reverse_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    reverse_iterator(pointer ptr = nullptr) : m_ptr(ptr) {}

    const_reference operator*() const { return *m_ptr; }
    reference operator*() { return *m_ptr; }
    pointer operator->() { return m_ptr; }
    const_pointer operator->() const { return m_ptr; }

    reverse_iterator& operator++() { --m_ptr; return *this; }
    reverse_iterator operator++(int) { reverse_iterator temp = *this; --(*this); return temp; }

    reverse_iterator& operator--() { ++m_ptr; return *this; }
    reverse_iterator operator--(int) { reverse_iterator temp = *this; ++(*this); return temp; }

    reverse_iterator operator+(difference_type n) const { return reverse_iterator(m_ptr - n); }
    reverse_iterator operator-(difference_type n) const { return reverse_iterator(m_ptr + n); }

    difference_type operator-(const reverse_iterator& other) const { return other.m_ptr - m_ptr; }

    reverse_iterator& operator+=(difference_type n) { m_ptr -= n; return *this; }
    reverse_iterator& operator-=(difference_type n) { m_ptr += n; return *this; }

    reference operator[](difference_type n) const { return *(m_ptr - n); }

    bool operator==(const reverse_iterator& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const reverse_iterator& other) const { return m_ptr != other.m_ptr; }
    bool operator<(const reverse_iterator& other) const { return m_ptr > other.m_ptr; }
    bool operator>(const reverse_iterator& other) const { return m_ptr < other.m_ptr; }
    bool operator<=(const reverse_iterator& other) const { return m_ptr >= other.m_ptr; }
    bool operator>=(const reverse_iterator& other) const { return m_ptr <= other.m_ptr; }

private:
    pointer m_ptr;
};

template<typename T>
class Vector<T>::const_reverse_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    const_reverse_iterator(pointer ptr = nullptr) : m_ptr(ptr) {}

    const_reference operator*() const { return *m_ptr; }
    const_pointer operator->() const { return m_ptr; }

    const_reverse_iterator& operator++() { --m_ptr; return *this; }
    const_reverse_iterator operator++(int) { const_reverse_iterator temp = *this; --(*this); return temp; }

    const_reverse_iterator& operator--() { ++m_ptr; return *this; }
    const_reverse_iterator operator--(int) { const_reverse_iterator temp = *this; ++(*this); return temp; }

    const_reverse_iterator operator+(difference_type n) const { return const_reverse_iterator(m_ptr - n); }
    const_reverse_iterator operator-(difference_type n) const { return const_reverse_iterator(m_ptr + n); }

    difference_type operator-(const const_reverse_iterator& other) const { return other.m_ptr - m_ptr; }

    const_reverse_iterator& operator+=(difference_type n) { m_ptr -= n; return *this; }
    const_reverse_iterator& operator-=(difference_type n) { m_ptr += n; return *this; }

    reference operator[](difference_type n) const { return *(m_ptr - n); }

    bool operator==(const const_reverse_iterator& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const const_reverse_iterator& other) const { return m_ptr != other.m_ptr; }
    bool operator<(const const_reverse_iterator& other) const { return m_ptr > other.m_ptr; }
    bool operator>(const const_reverse_iterator& other) const { return m_ptr < other.m_ptr; }
    bool operator<=(const const_reverse_iterator& other) const { return m_ptr >= other.m_ptr; }
    bool operator>=(const const_reverse_iterator& other) const { return m_ptr <= other.m_ptr; }

private:
    pointer m_ptr;
};

template <typename T>
concept Streamable = requires(std::ostream& os, const T& obj) {
    { os << obj } -> std::same_as<std::ostream&>;
};

template <Streamable T>
void print(const Vector<T>& vec) {
    for (typename Vector<T>::size_type i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

#include "Vector.tpp"

#endif // VECTOR_HPP
