#include "AVL.hpp"

#include <iostream>

int main() {
    AVL<int> avl;
    avl.insert(45);
    avl.insert(15);
    avl.insert(79);
    avl.insert(10);
    avl.insert(20);
    avl.insert(50);
    avl.insert(12);
    avl.insert(23);
    avl.insert(9);
    avl.insert(8);
    avl.remove(23);
    avl.remove(15);

    // std::cout << avl.getSuccessor(10) << std::endl << avl.getPredecessor(79);
    
    
    // avl.preOrderTraversal();
    // avl.postOrderTraversal();
    avl.inOrderTraversal();



}