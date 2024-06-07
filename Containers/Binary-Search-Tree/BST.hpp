#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <stack>

template <class T>
class BST {
struct Node;
public:
    BST() : root{nullptr} {}
    ~BST() {
        delete root;
    }
public:
    void insert(const T& value);
    Node* search(const T& target) const;
    Node* getRoot() const;
    size_t getHeight(Node* node) const;
    const T& getSuccessor(const T& val) const;
    const T& getPredecessor(const T& val) const;
    T getMax(Node* node) const;
    T getMin(Node* node) const;
    void remove(const T& value);
    void inOrderTraversal() const;
    void preOrderTraversal() const;
    void postOrderTraversal() const;
    void levelOrderTraversal() const;
    
private:
    Node* search(Node* root,const T& target) const;
    Node* insert(Node* root,const T& value);
    Node* getSuccessor(Node* node) const;
    Node* getPredecessor(Node* node) const;
    Node* remove(Node* node,const T& value);
    void inOrderTraversal(Node* node) const;
    void preOrderTraversal(Node* node) const;
    void postOrderTraversal(Node* node) const;


private:
    struct Node {
        T val;
        Node* left;
        Node* right;

        Node(const T& value) : val{value},left{nullptr},right{nullptr} {}

    };

    Node* root;

};


#include "BST.tpp"


#endif //BST_HPP
