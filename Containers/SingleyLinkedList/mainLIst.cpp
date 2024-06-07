#include "SinglyLinkedList.hpp"

int main()
{
    List<int> myList;

    myList.push_front(3);
    myList.push_front(2);
    myList.push_front(1);

    std::cout << "Original List: ";
    myList.print();

    std::cout << "Front element: " << myList.front() << std::endl;
    std::cout << "Back element: " << myList.back() << std::endl;

    myList.insert(1, 10);
    std::cout << "List after inserting 10 at position 1: ";
    myList.print();

    myList.erase(2);
    std::cout << "List after erasing element at position 2: ";
    myList.print();

    int valueToFind = 2;
    std::cout << "Is " << valueToFind << " in the list? " << (myList.find(valueToFind) ? "Yes" : "No") << std::endl;

    std::cout << "List using iterators: ";
    for (List<int>::iterator it = myList.begin(); it != myList.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    myList.clear();
    std::cout << "List after clearing: ";
    myList.print();

    return 0;
}
