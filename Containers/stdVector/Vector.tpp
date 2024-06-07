#ifndef VECTOR_TPP
#define VECTOR_TPP

template<typename T>
Vector<T>::Vector()
    : elements(nullptr), count(0), capacity_(0) {}

template<typename T>
Vector<T>::Vector(size_type count)
    : elements(new value_type[count]()), count(count), capacity_(count) {}

template<typename T>
Vector<T>::Vector(size_type count, const_reference value)
    : elements(new value_type[count]), count(count), capacity_(count) {
    std::uninitialized_fill_n(elements, count, value);
}

template<typename T>
template<typename InputIt>
Vector<T>::Vector(InputIt first, InputIt last)
    : elements(nullptr), count(0), capacity_(0) {
    for (auto it = first; it != last; ++it) {
        push_back(*it);
    }
}

template<typename T>
Vector<T>::Vector(const Vector& other)
    : elements(new value_type[other.capacity_]), count(other.count), capacity_(other.capacity_) {
    std::uninitialized_copy_n(other.elements, count, elements);
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : elements(other.elements), count(other.count), capacity_(other.capacity_) {
    other.elements = nullptr;
    other.count = 0;
    other.capacity_ = 0;
}

template<typename T>
Vector<T>::Vector(std::initializer_list<value_type> init)
    : elements(new value_type[init.size()]), count(init.size()), capacity_(init.size()) {
    std::uninitialized_copy(init.begin(), init.end(), elements);
}

template<typename T>
Vector<T>::~Vector() {
    destroy_elements();
    delete[] elements;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        destroy_elements();
        delete[] elements;
        count = other.count;
        capacity_ = other.capacity_;
        elements = new value_type[capacity_];
        std::uninitialized_copy_n(other.elements, count, elements);
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        destroy_elements();
        delete[] elements;
        elements = other.elements;
        count = other.count;
        capacity_ = other.capacity_;
        other.elements = nullptr;
        other.count = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<value_type> ilist) {
    destroy_elements();
    delete[] elements;
    count = ilist.size();
    capacity_ = ilist.size();
    elements = new value_type[capacity_];
    std::uninitialized_copy(ilist.begin(), ilist.end(), elements);
    return *this;
}

template<typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
    if (pos >= count) {
        throw std::out_of_range("Vector::at");
    }
    return elements[pos];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
    if (pos >= count) {
        throw std::out_of_range("Vector::at");
    }
    return elements[pos];
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
    return elements[pos];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
    return elements[pos];
}

template<typename T>
typename Vector<T>::reference Vector<T>::front() {
    return elements[0];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
    return elements[0];
}

template<typename T>
typename Vector<T>::reference Vector<T>::back() {
    return elements[count - 1];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
    return elements[count - 1];
}

template<typename T>
typename Vector<T>::pointer Vector<T>::data() noexcept {
    return elements;
}

template<typename T>
typename Vector<T>::const_pointer Vector<T>::data() const noexcept {
    return elements;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
    return iterator(elements);
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept {
    return const_iterator(elements);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
    return iterator(elements + count);
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept {
    return const_iterator(elements + count);
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept {
    return reverse_iterator(end());
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const noexcept {
    return const_reverse_iterator(end());
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept {
    return reverse_iterator(begin());
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const noexcept {
    return const_reverse_iterator(begin());
}

template<typename T>
bool Vector<T>::empty() const noexcept {
    return count == 0;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
    return count;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template<typename T>
void Vector<T>::reserve(size_type new_cap) {
    if (new_cap > capacity_) {
        reallocate(new_cap);
    }
}

template<typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
    return capacity_;
}

template<typename T>
void Vector<T>::shrink_to_fit() {
    if (count < capacity_) {
        reallocate(count);
    }
}

template<typename T>
void Vector<T>::clear() noexcept {
    destroy_elements();
    count = 0;
}

template<typename T>
void Vector<T>::assign(size_type count, const_reference value) {
    clear();
    if (count > capacity_) {
        reallocate(count);
    }
    std::uninitialized_fill_n(elements, count, value);
    this->count = count;
}

template<typename T>
template<typename InputIt>
void Vector<T>::assign(InputIt first, InputIt last) {
    clear();
    difference_type new_count = std::distance(first, last);
    if (new_count > capacity_) {
        reallocate(new_count);
    }
    std::uninitialized_copy(first, last, elements);
    count = new_count;
}

template<typename T>
void Vector<T>::assign(std::initializer_list<value_type> ilist) {
    assign(ilist.begin(), ilist.end());
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, const_reference value) {
    return emplace(pos, value);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, value_type&& value) {
    return emplace(pos, std::move(value));
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_type count, const_reference value) {
    difference_type offset = pos - begin();
    if (count == 0) return iterator(elements + offset);
    if (this->count + count > capacity_) {
        size_type new_capacity = this->count + count;
        pointer new_elements = new value_type[new_capacity];
        std::uninitialized_copy(begin(), pos, new_elements);
        std::uninitialized_fill_n(new_elements + offset, count, value);
        std::uninitialized_copy(pos, end(), new_elements + offset + count);
        destroy_elements();
        delete[] elements;
        elements = new_elements;
        capacity_ = new_capacity;
    } else {
        std::uninitialized_copy(pos, end(), elements + offset + count);
        std::uninitialized_fill_n(elements + offset, count, value);
    }
    this->count += count;
    return iterator(elements + offset);
}

template<typename T>
template<typename InputIt>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, InputIt first, InputIt last) {
    difference_type offset = pos - begin();
    difference_type count = last - first;
    if (count == 0) return iterator(elements + offset);
    if (this->count + count > capacity_) {
        size_type new_capacity = this->count + count;
        pointer new_elements = new value_type[new_capacity];
        std::uninitialized_copy(begin(), pos, new_elements);
        std::uninitialized_copy(first, last, new_elements + offset);
        std::uninitialized_copy(pos, end(), new_elements + offset + count);
        destroy_elements();
        delete[] elements;
        elements = new_elements;
        capacity_ = new_capacity;
    } else {
        std::uninitialized_copy(pos, end(), elements + offset + count);
        std::uninitialized_copy(first, last, elements + offset);
    }
    this->count += count;
    return iterator(elements + offset);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, std::initializer_list<value_type> ilist) {
    return insert(pos, ilist.begin(), ilist.end());
}

template<typename T>
template<typename... Args>
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos, Args&&... args) {
    difference_type offset = pos - begin();
    if (count == capacity_) {
        size_type new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
        pointer new_elements = new value_type[new_capacity];
        std::uninitialized_copy(begin(), pos, new_elements);
        new(new_elements + offset) value_type(std::forward<Args>(args)...); // In-place new operator
        std::uninitialized_copy(pos, end(), new_elements + offset + 1);
        destroy_elements();
        delete[] elements;
        elements = new_elements;
        capacity_ = new_capacity;
    } else {
        std::uninitialized_copy(pos, end(), elements + offset + 1);
        new(elements + offset) value_type(std::forward<Args>(args)...); // In-place new operator
    }
    ++count;
    return iterator(elements + offset);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator pos) {
    return erase(pos, pos + 1);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator first, const_iterator last) {
    if (first == last) return iterator(const_cast<pointer>(first));
    difference_type count_to_erase = last - first;
    difference_type offset = first - begin();
    std::move(last, end(), const_cast<pointer>(first));
    for (pointer it = elements + count - count_to_erase; it != elements + count; ++it) {
        it->~value_type();
    }
    count -= count_to_erase;
    return iterator(elements + offset);
}

template<typename T>
void Vector<T>::push_back(const_reference value) {
    emplace_back(value);
}

template<typename T>
void Vector<T>::push_back(value_type&& value) {
    emplace_back(std::move(value));
}

template<typename T>
template<typename... Args>
typename Vector<T>::reference Vector<T>::emplace_back(Args&&... args) {
    if (count == capacity_) {
        size_type new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
        pointer new_elements = new value_type[new_capacity];
        std::uninitialized_copy(elements, elements + count, new_elements);
        new(new_elements + count) value_type(std::forward<Args>(args)...); // In-place new operator
        destroy_elements();
        delete[] elements;
        elements = new_elements;
        capacity_ = new_capacity;
    } else {
        new(elements + count) value_type(std::forward<Args>(args)...); // In-place new operator
    }
    ++count;
    return elements[count - 1];
}

template<typename T>
void Vector<T>::pop_back() {
    if (count > 0) {
        elements[count - 1].~value_type();
        --count;
    }
}

template<typename T>
void Vector<T>::resize(size_type new_count) {
    if (new_count > count) {
        if (new_count > capacity_) {
            reallocate(new_count);
        }
        std::uninitialized_value_construct_n(elements + count, new_count - count);
    } else {
        for (pointer it = elements + new_count; it != elements + count; ++it) {
            it->~value_type();
        }
    }
    count = new_count;
}

template<typename T>
void Vector<T>::resize(size_type new_count, const_reference value) {
    if (new_count > count) {
        if (new_count > capacity_) {
            reallocate(new_count);
        }
        std::uninitialized_fill_n(elements + count, new_count - count, value);
    } else {
        for (pointer it = elements + new_count; it != elements + count; ++it) {
            it->~value_type();
        }
    }
    count = new_count;
}

template<typename T>
void Vector<T>::swap(Vector& other) noexcept {
    std::swap(elements, other.elements);
    std::swap(count, other.count);
    std::swap(capacity_, other.capacity_);
}

template<typename T>
template<typename... Args>
typename Vector<T>::iterator Vector<T>::append_range(Args&&... args) {
    return insert(end(), std::forward<Args>(args)...);
}

template<typename T>
void Vector<T>::reallocate(size_type new_cap) {
    pointer new_elements = new value_type[new_cap];
    std::uninitialized_copy(elements, elements + count, new_elements);
    destroy_elements();
    delete[] elements;
    elements = new_elements;
    capacity_ = new_cap;
}

template<typename T>
void Vector<T>::destroy_elements() {
    for (pointer it = elements; it != elements + count; ++it) {
        it->~value_type();
    }
}


template<typename T>
void Vector<T>::print() const {
    for (size_type i = 0; i < count; ++i) {
        std::cout << elements[i] << " ";
    }
    std::cout << std::endl;
}


// Implementation for nested iterator class
template<typename T>
class Vector<T>::iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    iterator(pointer ptr) : ptr_(ptr) {}

    reference operator*() const { return *ptr_; }
    pointer operator->() { return ptr_; }
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

// Proxy class for operator[]
template<typename T>
class Vector<T>::proxy {
public:
    proxy(reference ref) : ref_(ref) {}

    operator reference() const { return ref_; }
    proxy& operator=(const value_type& value) { ref_ = value; return *this; }
    proxy& operator=(value_type&& value) { ref_ = std::move(value); return *this; }

private:
    reference ref_;
};

#endif // VECTOR_TPP
