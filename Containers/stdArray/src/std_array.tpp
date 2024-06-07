#ifndef STD_ARRAY_TPP
#define STD_ARRAY_TPP

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type index) {
    if (index >= N) {
        throw std::out_of_range("Index out of range");
    }
    return elements[index];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::at(size_type index) const {
    if (index >= N) {
        throw std::out_of_range("Index out of range");
    }
    return elements[index];
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type index) {
    return elements[index];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::operator[](size_type index) const {
    return elements[index];
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::front() {
    return elements[0];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() const {
    return elements[0];
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::back() {
    return elements[N - 1];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() const {
    return elements[N - 1];
}

template <typename T, std::size_t N>
typename Array<T, N>::pointer Array<T, N>::data() noexcept {
    return elements;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_pointer Array<T, N>::data() const noexcept {
    return elements;
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() noexcept {
    return elements;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::begin() const noexcept {
    return elements;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::cbegin() const noexcept {
    return elements;
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::end() noexcept {
    return elements + N;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::end() const noexcept {
    return elements + N;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::cend() const noexcept {
    return elements + N;
}

template <typename T, std::size_t N>
typename Array<T, N>::reverse_iterator Array<T, N>::rbegin() noexcept {
    return reverse_iterator(end());
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reverse_iterator Array<T, N>::rbegin() const noexcept {
    return const_reverse_iterator(end());
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reverse_iterator Array<T, N>::crbegin() const noexcept {
    return const_reverse_iterator(cend());
}

template <typename T, std::size_t N>
typename Array<T, N>::reverse_iterator Array<T, N>::rend() noexcept {
    return reverse_iterator(begin());
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reverse_iterator Array<T, N>::rend() const noexcept {
    return const_reverse_iterator(begin());
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reverse_iterator Array<T, N>::crend() const noexcept {
    return const_reverse_iterator(cbegin());
}

template <typename T, std::size_t N>
bool Array<T, N>::empty() const noexcept {
    return N == 0;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type Array<T, N>::size() const noexcept {
    return N;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() const noexcept {
    return N;
}

template <typename T, std::size_t N>
void Array<T, N>::fill(const T& value) {
    for (size_type i = 0; i < N; ++i) {
        elements[i] = value;
    }
}

template <typename T, std::size_t N>
void Array<T, N>::swap(Array& other) noexcept {
    for (size_type i = 0; i < N; ++i) {
        std::swap(elements[i], other.elements[i]);
    }
}



#endif // STD_ARRAY_TPP
