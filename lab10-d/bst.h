#ifndef BST_H
#define BST_H

#include <iostream>

template <class T>
struct nodeType
{
    T data;                    ///< Data stored in the node
    nodeType<T>* left;         ///< Pointer to left child
    nodeType<T>* right;        ///< Pointer to right child

    /// Constructor
    nodeType(const T& value) : data(value), left(nullptr), right(nullptr) {}
};


template <class T>
class BinarySearchTree
{
public:

    typedef void (*FunctionType)(T&);

    // Constructors and Destructor
    BinarySearchTree();                                          ///< Default constructor
    ~BinarySearchTree();                                         ///< Destructor
    BinarySearchTree(const BinarySearchTree<T>& other);         ///< Copy constructor
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other); ///< Assignment operator

    // Core BST operations
    void insertElement(const T& value);                         ///< Insert element into BST
    bool searchElement(const T& value) const;                   ///< Search for element in BST
    bool isEmpty() const;                                        ///< Check if BST is empty
    void destroyTree();                                          ///< Clear all nodes from BST

    // Traversal operations with function pointers (following textbook approach)
    void inOrderTraversal(FunctionType visitFunction) const;    ///< In-order traversal with callback
    void preOrderTraversal(FunctionType visitFunction) const;   ///< Pre-order traversal with callback
    void postOrderTraversal(FunctionType visitFunction) const;  ///< Post-order traversal with callback

private:
    nodeType<T>* root;                                          ///< Root of the BST

    // Private helper methods (following textbook naming convention)
    nodeType<T>* insertRecursive(nodeType<T>* node, const T& value);
    bool searchRecursive(nodeType<T>* node, const T& value) const;
    void inOrder(FunctionType visitFunction, nodeType<T>* node) const;      // Textbook naming
    void preOrder(FunctionType visitFunction, nodeType<T>* node) const;     // Textbook naming
    void postOrder(FunctionType visitFunction, nodeType<T>* node) const;    // Textbook naming
    void destroyRecursive(nodeType<T>* node);
    nodeType<T>* copyTree(nodeType<T>* node);
};

// Template Implementation
// Interface and implementation are separated for better code organization
// and to follow the principle of separating declaration from definition

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr)
{
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    destroyTree();
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other) : root(nullptr)
{
    root = copyTree(other.root);
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other)
{
    if (this != &other)
    {
        destroyTree();
        root = copyTree(other.root);
    }
    return *this;
}

template <class T>
void BinarySearchTree<T>::insertElement(const T& value)
{
    root = insertRecursive(root, value);
}

template <class T>
nodeType<T>* BinarySearchTree<T>::insertRecursive(nodeType<T>* node, const T& value)
{
    if (node == nullptr)
    {
        return new nodeType<T>(value);
    }

    if (value < node->data)
    {
        node->left = insertRecursive(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = insertRecursive(node->right, value);
    }
    // If value equals node->data, don't insert (no duplicates)

    return node;
}

template <class T>
bool BinarySearchTree<T>::searchElement(const T& value) const
{
    return searchRecursive(root, value);
}

template <class T>
bool BinarySearchTree<T>::searchRecursive(nodeType<T>* node, const T& value) const
{
    if (node == nullptr)
    {
        return false;
    }

    if (value == node->data)
    {
        return true;
    }

    if (value < node->data)
    {
        return searchRecursive(node->left, value);
    }
    else
    {
        return searchRecursive(node->right, value);
    }
}

template <class T>
bool BinarySearchTree<T>::isEmpty() const
{
    return root == nullptr;
}

template <class T>
void BinarySearchTree<T>::destroyTree()
{
    destroyRecursive(root);
    root = nullptr;
}

template <class T>
void BinarySearchTree<T>::destroyRecursive(nodeType<T>* node)
{
    if (node != nullptr)
    {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

template <class T>
nodeType<T>* BinarySearchTree<T>::copyTree(nodeType<T>* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    nodeType<T>* newNode = new nodeType<T>(node->data);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

// Traversal implementations with function pointers (following textbook approach)
template <class T>
void BinarySearchTree<T>::inOrderTraversal(FunctionType visitFunction) const
{
    inOrder(visitFunction, root);
}

template <class T>
void BinarySearchTree<T>::inOrder(FunctionType visitFunction, nodeType<T>* node) const
{
    if (node != nullptr)
    {
        inOrder(visitFunction, node->left);
        (*visitFunction)(node->data);               // Textbook style function pointer call
        inOrder(visitFunction, node->right);
    }
}

template <class T>
void BinarySearchTree<T>::preOrderTraversal(FunctionType visitFunction) const
{
    preOrder(visitFunction, root);
}

template <class T>
void BinarySearchTree<T>::preOrder(FunctionType visitFunction, nodeType<T>* node) const
{
    if (node != nullptr)
    {
        (*visitFunction)(node->data);           // Textbook style function pointer call
        preOrder(visitFunction, node->left);
        preOrder(visitFunction, node->right);
    }
}

template <class T>
void BinarySearchTree<T>::postOrderTraversal(FunctionType visitFunction) const
{
    postOrder(visitFunction, root);
}

template <class T>
void BinarySearchTree<T>::postOrder(FunctionType visitFunction, nodeType<T>* node) const
{
    if (node != nullptr)
    {
        postOrder(visitFunction, node->left);
        postOrder(visitFunction, node->right);
        (*visitFunction)(node->data);           // Textbook style function pointer call
    }
}

#endif // BINARYSEARCHTREE_H
