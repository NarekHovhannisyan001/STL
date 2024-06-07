#ifndef MYSET_TPP
#define MYSET_TPP

template <class T>
MySet<T>::MySet() : m_bucket(7),m_size(0) {
}

template <class T>
MySet<T>::~MySet() {
}

template <class T>
template <class R>
size_t MySet<T>::hashFunction(const R& val,size_t size) const {
    size_t res = 7919;
    res ^= 23;
    res = (res << 12);
    return (res * val) % size;
}


template <class T>
void MySet<T>::insert(const T& val) {
    size_t index = hashFunction(val, m_bucket.size());

    if (!find(val)) {
        m_bucket[index].push_front(val);
        ++m_size;
        if (getLF() > 0.7) {
            reHash();
        }
    } 
}

template<class T>
bool MySet<T>::find(const T& val) const {
    size_t index = hashFunction(val, m_bucket.size());
    for (auto i = m_bucket[index].begin();i != m_bucket[index].end(); ++i) {
        if (*i == val) {
            return true;
        }
    }
    return false;
}


template <class T>
void MySet<T>::remove(const T& val) {
    size_t index = hashFunction(val, m_bucket.size());

    if (find(val)) {
        auto& bucket = m_bucket[index];
        bucket.remove(val);
        --m_size;
    }
}


template <class T>
double MySet<T>::getLF() const {
    return (double)m_size / m_bucket.size();
}



template <class T>
bool MySet<T>::is_prime(size_t num) {
    if (num < 2) {
        return false;
    }
    if (num == 2 || num == 3) {
        return true;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

template <class T>
size_t MySet<T>::next_prime(size_t start) {
    size_t next = start + 1;
    while (!is_prime(next)) {
        next++;
    }
    return next;
}


template <class T>
void MySet<T>::reHash() {
    Vector<std::forward_list<T>> newBucket(next_prime(m_bucket.size()));
    for (const auto& bucket : m_bucket) {
        for (const auto& val : bucket) {
            size_t newIndex = hashFunction(val, newBucket.size());
            newBucket[newIndex].push_front(val);
        }
    }
    m_bucket = std::move(newBucket);
    
}





#endif // MYSET_TPP