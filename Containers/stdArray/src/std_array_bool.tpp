#ifndef STD_ARRAY_BOOL_TPP
#define STD_ARRAY_BOOL_TPP

template <std::size_t N>
Array<bool, N>::Array() {
    fill(false);
}

template <std::size_t N>
Array<bool, N>::Array(const Array& other) {
    for (std::size_t i = 0; i < (N + 7) / 8; ++i) {
        bits[i] = other.bits[i];
    }
}

template <std::size_t N>
Array<bool, N>& Array<bool, N>::operator=(const Array& other) {
    if (this != &other) {
        for (std::size_t i = 0; i < (N + 7) / 8; ++i) {
            bits[i] = other.bits[i];
        }
    }
    return *this;
}

template <std::size_t N>
bool Array<bool, N>::operator[](std::size_t index) const {
    if (index >= N) {
        throw std::out_of_range("Index out of range");
    }
    return bits[index / 8] & (1 << (index % 8));
}

template <std::size_t N>
typename Array<bool, N>::Proxy Array<bool, N>::operator[](std::size_t index) {
    if (index >= N) {
        throw std::out_of_range("Index out of range");
    }
    return Proxy(bits[index / 8], index % 8);
}

template <std::size_t N>
typename Array<bool, N>::Proxy Array<bool, N>::at(std::size_t index) {
    if (index >= N) {
        throw std::out_of_range("Index out of range");
    }
    return Proxy(bits[index / 8], index % 8);
}

template <std::size_t N>
bool Array<bool, N>::at(std::size_t index) const {
    if (index >= N) {
        throw std::out_of_range("Index out of range");
    }
    return bits[index / 8] & (1 << (index % 8));
}

template <std::size_t N>
typename Array<bool, N>::iterator Array<bool, N>::begin() {
    return Iterator(bits, 0);
}

template <std::size_t N>
typename Array<bool, N>::iterator Array<bool, N>::end() {
    return Iterator(bits, N);
}

template <std::size_t N>
typename Array<bool, N>::const_iterator Array<bool, N>::begin() const {
    return ConstIterator(bits, 0);
}

template <std::size_t N>
typename Array<bool, N>::const_iterator Array<bool, N>::end() const {
    return ConstIterator(bits, N);
}

template <std::size_t N>
typename Array<bool, N>::reverse_iterator Array<bool, N>::rbegin() {
    return reverse_iterator(end());
}

template <std::size_t N>
typename Array<bool, N>::reverse_iterator Array<bool, N>::rend() {
    return reverse_iterator(begin());
}

template <std::size_t N>
typename Array<bool, N>::const_reverse_iterator Array<bool, N>::rbegin() const {
    return const_reverse_iterator(end());
}

template <std::size_t N>
typename Array<bool, N>::const_reverse_iterator Array<bool, N>::rend() const {
    return const_reverse_iterator(begin());
}

template <std::size_t N>
typename Array<bool, N>::size_type Array<bool, N>::size() const noexcept {
    return N;
}

template <std::size_t N>
bool Array<bool, N>::empty() const noexcept {
    return N == 0;
}

template <std::size_t N>
typename Array<bool, N>::size_type Array<bool, N>::max_size() const noexcept {
    return N;
}

template <std::size_t N>
void Array<bool, N>::fill(bool value) {
    unsigned char byte_value = value ? 0xFF : 0x00;
    for (std::size_t i = 0; i < (N + 7) / 8; ++i) {
        bits[i] = byte_value;
    }
}

template <std::size_t N>
void Array<bool, N>::swap(Array& other) noexcept {
    for (std::size_t i = 0; i < (N + 7) / 8; ++i) {
        std::swap(bits[i], other.bits[i]);
    }
}

// Proxy and Iterator implementations...

template <std::size_t N>
Array<bool, N>::Proxy::Proxy(unsigned char& byte, std::size_t bit)
    : byte_(byte), bit_(bit) {}

template <std::size_t N>
typename Array<bool, N>::Proxy& Array<bool, N>::Proxy::operator=(bool value) {
    if (value) {
        byte_ |= (1 << bit_);
    } else {
        byte_ &= ~(1 << bit_);
    }
    return *this;
}

template <std::size_t N>
Array<bool, N>::Proxy::operator bool() const {
    return byte_ & (1 << bit_);
}

template <std::size_t N>
Array<bool, N>::ConstIterator::ConstIterator(const unsigned char* data, std::size_t bit_pos)
    : data_(data), bit_pos_(bit_pos) {}

template <std::size_t N>
typename Array<bool, N>::ConstIterator& Array<bool, N>::ConstIterator::operator++() {
    ++bit_pos_;
    return *this;
}

template <std::size_t N>
typename Array<bool, N>::ConstIterator Array<bool, N>::ConstIterator::operator++(int) {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

template <std::size_t N>
bool Array<bool, N>::ConstIterator::operator==(const ConstIterator& other) const {
    return bit_pos_ == other.bit_pos_;
}

template <std::size_t N>
bool Array<bool, N>::ConstIterator::operator!=(const ConstIterator& other) const {
    return !(*this == other);
}

template <std::size_t N>
bool Array<bool, N>::ConstIterator::operator*() const {
    return data_[bit_pos_ / 8] & (1 << (bit_pos_ % 8));
}

template <std::size_t N>
Array<bool, N>::Iterator::Iterator(unsigned char* data, std::size_t bit_pos)
    : ConstIterator(data, bit_pos), data_(data) {}

template <std::size_t N>
typename Array<bool, N>::Iterator& Array<bool, N>::Iterator::operator++() {
    ++this->bit_pos_;
    return *this;
}

template <std::size_t N>
typename Array<bool, N>::Iterator Array<bool, N>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <std::size_t N>
typename Array<bool, N>::Proxy Array<bool, N>::Iterator::operator*() {
    return Proxy(data_[this->bit_pos_ / 8], this->bit_pos_ % 8);
}


#endif // STD_ARRAY_BOOL_TPP
