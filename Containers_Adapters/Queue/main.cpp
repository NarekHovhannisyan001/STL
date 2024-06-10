#include <iostream>
#include "Queue.hpp"

int main() {
    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    std::cout << "Queue size: " << queue.size() << std::endl;
    std::cout << "Front element: " << queue.front() << std::endl;
    std::cout << "Back element: " << queue.back() << std::endl;

    queue.dequeue();
    std::cout << "Front element after dequeue: " << queue.front() << std::endl;

    queue.dequeue();
    queue.dequeue();

    if (queue.empty()) {
        std::cout << "Queue is empty." << std::endl;
    }

    return 0;
}
