#ifndef PIQ_TPP
#define PIQ_TPP


template <class T, class Comp>
Proarity_queue<T, Comp>::Proarity_queue(const Comp& comp) : compar(comp) {
}

template <class T, class Comp>
Proarity_queue<T, Comp>::Proarity_queue(const std::vector<T>& vec) : m_arr(vec) {
    buildHeap();
}

template <class T, class Comp>
const T& Proarity_queue<T, Comp>::top() const {
    if (m_arr.empty()) {
        throw std::runtime_error("The heap is empty");
    }

    return m_arr[0];
}

template <class T, class Comp>
void Proarity_queue<T, Comp>::push(const T& value) {
    m_arr.push_back(value);
    int index = m_arr.size() - 1;
    while (index > 0) {
        int parentIndex = (index - 1) / 2;

        if (compar(m_arr[parentIndex], m_arr[index])) {
            std::swap(m_arr[index], m_arr[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

template <typename T, typename Comp>
bool Proarity_queue<T, Comp>::empty() const
{
    return m_arr.empty();
}

template <class T, class Comp>
void Proarity_queue<T, Comp>::pop() {
    if (m_arr.empty()) {
        throw std::runtime_error("Heap is empty");
    }

    m_arr[0] = m_arr.back();
    m_arr.pop_back();
    heapify(0);
}

template <class T, class Comp>
void Proarity_queue<T, Comp>::heapify(size_t index) {
    size_t leftChild = 2 * index + 1;
    size_t rightChild = 2 * index + 2;
    size_t largest = index;

    if (leftChild < m_arr.size() && compar(m_arr[largest], m_arr[leftChild])) {
        largest = leftChild;
    }

    if (rightChild < m_arr.size() && compar(m_arr[largest], m_arr[rightChild])) {
        largest = rightChild;
    }

    if (largest != index) {
        std::swap(m_arr[index], m_arr[largest]);
        heapify(largest);
    }
}




template <class T, class Comp>
void Proarity_queue<T, Comp>::buildHeap() {
    for (int i = m_arr.size() / 2 - 1; i >= 0; --i) {
        heapify(static_cast<size_t>(i));
    }
}

template <class T, class Comp>
void Proarity_queue<T, Comp>::display() const {
    for (const auto& i : m_arr) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
}

#endif // PIQ_TPP
