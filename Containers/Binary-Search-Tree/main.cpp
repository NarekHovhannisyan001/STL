#include "BST.hpp"

#include <iostream>

int main() {
    BST<int> bst;
    bst.insert(45);
    bst.insert(15);
    bst.insert(79);
    bst.insert(10);
    bst.insert(20);
    bst.insert(50);
    bst.insert(12);
    bst.insert(23);
    bst.remove(23);
    bst.remove(15);

    // std::cout << bst.getSuccessor(10) << std::endl << bst.getPredecessor(79);
    
    
    // bst.preOrderTraversal();
    // bst.postOrderTraversal();
    bst.inOrderTraversal();



}