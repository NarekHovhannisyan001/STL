#ifndef AVL_TPP
#define AVL_TPP

template <class T>
typename AVL<T>::Node *AVL<T>::search(Node *root, const T &target) const
{
    if (!root || root->val == target)
    {
        return root;
    }

    if (root->val < target)
    {
        return search(root->right, target);
    }

    return search(root->left, target);
}

template <class T>
typename AVL<T>::Node *AVL<T>::search(const T &target) const
{
    return search(root, target);
}

template <class T>
size_t AVL<T>::getHeight(Node *node) const
{
    if (!node)
    {
        return 0;
    }

    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

template <class T>
T AVL<T>::getMax(Node *node) const
{
    if (!node)
    {
        throw std::runtime_error("Is not max");
    }

    while (node->right)
    {
        node = node->right;
    }

    return node->val;
}

template <class T>
T AVL<T>::getMin(Node *node) const
{
    if (!node)
    {
        throw std::runtime_error("Is not min");
    }

    while (node->left)
    {
        node = node->left;
    }

    return node->val;
}

template <class T>
typename AVL<T>::Node* AVL<T>::getRoot() const
{
    return root;
}


template <class T>
void AVL<T>::insert(const T &value)
{
    root = insert(root, value);
}

template <class T>
typename AVL<T>::Node *AVL<T>::insert(Node *node, const T &value)
{
    if (!node)
    {
        return new Node(value);
    }
    if (node->val < value)
    {
        node->right = insert(node->right, value);
    }
    else
    {
        node->left = insert(node->left, value);
    }

    int bf = getBalanceFactor(node);

    if (bf < -1 && value < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    } 
    if (bf < -1 && value > node->right->val) {
        return leftRotate(node);
    }

    if (bf > 1 && value < node->left->val) {
        return rightRotate(node);
    }

    if (bf > 1 && value > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    return node;

}

template <class T>
const T &AVL<T>::getSuccessor(const T &value) const
{
    if (!root)
    {
        throw std::runtime_error("Tree is empty ");
    }

    Node *tmp = getSuccessor(search(root,value));
    if (!tmp)
    {
        throw std::runtime_error("Don't have successor ");
    }

    return tmp->val;
}

template <class T>
typename AVL<T>::Node *AVL<T>::getSuccessor(Node *node) const
{
    if (!node)
    {
        return node;
    }
    if (node->right)
    {
        return search(getMin(node->right));
    }
    else
    {
        Node *curr = root;
        Node *successor = nullptr;
        while (curr != node)
        {
            if (node->val < curr->val)
            {
                successor = curr;
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }
        return successor;
    }
}

template <class T>
const T &AVL<T>::getPredecessor(const T &value) const
{
   if (!root)
    {
        throw std::runtime_error("Tree is empty");
    }

    Node *tmp = getPredecessor(search(value));
    if (!tmp)
    {
        throw std::runtime_error("Don't have predecessor");
    }

    return tmp->val;
}

template <class T>
typename AVL<T>::Node *AVL<T>::getPredecessor(Node *node) const
{
    if (!node)
    {
        return node;
    }

    if (node->left)
    {
        return search(getMax(node->left));
    }
    else
    {
        Node *curr = root;
        Node *predecessor = nullptr;
        while (curr != node)
        {
            if (node->val < curr->val)
            {
                curr = curr->left;
            }
            else
            {
                predecessor = curr;
                curr = curr->right;
            }
        }

        return predecessor;
    }
}

template <class T>
void AVL<T>::remove(const T &value)
{
    root = remove(root, value);
}

template <class T>
typename AVL<T>::Node *AVL<T>::remove(Node *node, const T &value)
{
    if (!node)
    {
        return node;
    }

    if (value < node->val)
    {
        node->left = remove(node->left, value);
    }
    else if (value > node->val)
    {
        node->right = remove(node->right, value);
    }
    else
    {
        if (!node->left)
        {
            Node *temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right)
        {
            Node *temp = node->left;
            delete node;
            return temp;
        }

        Node *temp = getSuccessor(node);
        node->val = temp->val;
        node->right = remove(node->right, temp->val);
    }


    int bf = getBalanceFactor(node);

    if (bf < -1 && value < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    } 
    if (bf < -1 && value > node->right->val) {
        return leftRotate(node);
    }

    if (bf > 1 && value < node->left->val) {
        return rightRotate(node);
    }

    if (bf > 1 && value > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    return node;
}

template <class T>
void AVL<T>::inOrderTraversal() const
{
    inOrderTraversal(root);
}

template <class T>
void AVL<T>::inOrderTraversal(Node *node) const
{
    if (!node)
        return;
    std::stack<Node *> stack;
    stack.push(node);
    Node *curr = node->left;

    while (curr || !stack.empty())
    {
        while (curr)
        {
            stack.push(curr);
            curr = curr->left;
        }
        Node *tmp = stack.top();
        stack.pop();
        std::cout << tmp->val << "  ";
        curr = tmp->right;
    }
}

template <class T>
void AVL<T>::preOrderTraversal() const
{
    preOrderTraversal(root);
}

template <class T>
void AVL<T>::preOrderTraversal(Node *node) const
{
    if (!node)
        return;
    std::stack<Node *> stack;
    stack.push(node);

    while (!stack.empty())
    {
        Node* curr = stack.top();
        stack.pop();
        std::cout << curr->val << "  ";

        if (curr->right) {
            stack.push(curr->right);
        }
        if (curr->left) {
            stack.push(curr->left);
        }
    }
    
}

template <class T>
void AVL<T>::postOrderTraversal() const
{
    postOrderTraversal(root);
}

template <class T>
void AVL<T>::postOrderTraversal(Node *node) const
{
    if (!node) return;
    std::stack<Node *> stack1;
    std::stack<Node *> stack2;
    stack1.push(node);

    while (!stack1.empty())
    {
        Node* curr = stack1.top();
        stack1.pop();
        stack2.push(curr);

        if (curr->left) {
            stack1.push(curr->left);
        }

        if (curr->right) {
            stack1.push(curr->right);
        }
    }

    while (!stack2.empty())
    {
        Node* curr = stack2.top();
        std::cout << curr->val << "  ";
        stack2.pop();
    }
    
    
}


template <class T>
int AVL<T>::getBalanceFactor(Node* node) const {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}


template <class T>
typename AVL<T>::Node *AVL<T>::leftRotate(Node *node) {
    if (!node) return node;

    Node* y = node->right;
    node->right = y->left;
    y->left = node;
    return y;
}

template <class T>
typename AVL<T>::Node *AVL<T>::rightRotate(Node *node) {
    if (!node) return node;

    Node* y = node->left;
    node->left = y->right;
    y->right = node;
    return y;
}



template<class T>
void AVL<T>::levelOrderTraversal() const {
    if (!root) return root;

    std::queue<Node *> queue;
    queue.push(root);

    while (!queue.empty())
    {
        Node* curr = queue.front();
        queue.pop();
        std::cout << curr->val << "  ";

        if (curr->left) {
            queue.push(curr->left);
        }
        if (curr->right) {
            queue.push(curr->right);
        }
    }
    

}

#endif // AVL_TPP