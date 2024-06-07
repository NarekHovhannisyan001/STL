#ifndef STD_ARRAY_BOOL_HPP
#define STD_ARRAY_BOOL_HPP

#include <cstddef>
#include <stdexcept>
#include <iterator>

template <std::size_t N>
class Array<bool, N> {
public:
    using value_type = bool;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    class Proxy {
    public:
        Proxy(unsigned char& byte, std::size_t bit);
        Proxy& operator=(bool value);
        operator bool() const;

    private:
        unsigned char& byte_;
        std::size_t bit_;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = bool;
        using pointer = const bool*;
        using reference = const bool&;

        ConstIterator(const unsigned char* data, std::size_t bit_pos);

        ConstIterator& operator++();
        ConstIterator operator++(int);

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

        bool operator*() const;

    protected:
        const unsigned char* data_;
        std::size_t bit_pos_;
    };

    class Iterator : public ConstIterator {
    public:
        Iterator(unsigned char* data, std::size_t bit_pos);

        Iterator& operator++();
        Iterator operator++(int);

        Proxy operator*();

    private:
        unsigned char* data_;
    };

    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Array();
    Array(const Array& other);
    Array& operator=(const Array& other);

    bool operator[](size_type index) const;
    Proxy operator[](size_type index);

    Proxy at(size_type index);
    bool at(size_type index) const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    size_type size() const noexcept;
    bool empty() const noexcept;
    size_type max_size() const noexcept;
    void fill(bool value);
    void swap(Array& other) noexcept;

private:
    unsigned char bits[(N + 7) / 8]; // Bitset storage
};

#include "../src/std_array_bool.tpp"

#endif // STD_ARRAY_BOOL_HPP
