#ifndef BST_H
#define BST_H

#include <iostream>

/**
 * @file bst.h
 * @brief Minimal Binary Search Tree implementation
 * @author Dhruv Goswami
 * @date 20/06/2025
 *
 * Rationale for struct encapsulation:
 * nodeType uses struct because it's a simple data container with public access needed.
 * All members are data with no complex invariants to maintain.
 * This allows direct access while keeping the design simple and efficient.
 * Alternative approaches (private members with friend classes) would add unnecessary complexity
 * for what is essentially a simple data holder.
 */

template <class T>
struct nodeType
{
    T data;                    ///< Data stored in the node
    nodeType<T>* left;         ///< Pointer to left child
    nodeType<T>* right;        ///< Pointer to right child

    /// Constructor
    nodeType(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

/**
 * @brief Minimal Binary Search Tree class
 *
 * Rationale for class encapsulation:
 * BinarySearchTree uses class because it maintains important invariants (BST property)
 * and needs to control access to internal structure. Private members ensure
 * the BST property is never violated by external code.
 *
 * This is MINIMAL - only essential operations included:
 * - Insert, Search, Destroy (core BST operations)
 * - Traversals with function pointers (for flexibility)
 * - Constructor/Destructor (memory management)
 *
 * Specifically EXCLUDED from minimal design:
 * - isEmpty() - not essential, can check root directly if needed
 * - height() - not core BST functionality
 * - nodeCount() - not essential for BST behavior
 * - complex deletion operations - not required for minimal implementation
 */
template <class T>
class BinarySearchTree
{
public:
    typedef void (*f1Typ)(T&);  ///< Function pointer type for traversals
                                ///< Single parameter with read/write access
                                ///< Rationale: Allows client to both read and modify data
                                ///< during traversal, providing maximum flexibility

    // Constructors and Destructor
    BinarySearchTree();                                          ///< Default constructor
    ~BinarySearchTree();                                         ///< Destructor
    BinarySearchTree(const BinarySearchTree<T>& other);         ///< Copy constructor
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other); ///< Assignment operator

    // Core BST operations (MINIMAL set)
    void insertElement(const T& value);                         ///< Insert element into BST
    bool searchElement(const T& value) const;                   ///< Search for element in BST
    void destroyTree();                                          ///< Clear all nodes from BST

    // Traversal operations with function pointers
    void inOrderTraversal(f1Typ f1) const;                     ///< In-order traversal with callback
    void preOrderTraversal(f1Typ f1) const;                    ///< Pre-order traversal with callback
    void postOrderTraversal(f1Typ f1) const;                   ///< Post-order traversal with callback

private:
    nodeType<T>* root;                                          ///< Root of the BST

    // Private helper methods
    nodeType<T>* insertRecursive(nodeType<T>* node, const T& value);
    bool searchRecursive(nodeType<T>* node, const T& value) const;
    void inOrder(f1Typ f1, nodeType<T>* node) const;
    void preOrder(f1Typ f1, nodeType<T>* node) const;
    void postOrder(f1Typ f1, nodeType<T>* node) const;
    void destroyRecursive(nodeType<T>* node);
    nodeType<T>* copyTree(nodeType<T>* node);
};

// Template Implementation

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

// Traversal implementations with function pointers
template <class T>
void BinarySearchTree<T>::inOrderTraversal(f1Typ f1) const
{
    inOrder(f1, root);
}

template <class T>
void BinarySearchTree<T>::inOrder(f1Typ f1, nodeType<T>* node) const
{
    if (node != nullptr)
    {
        inOrder(f1, node->left);
        (*f1)(node->data);
        inOrder(f1, node->right);
    }
}

template <class T>
void BinarySearchTree<T>::preOrderTraversal(f1Typ f1) const
{
    preOrder(f1, root);
}

template <class T>
void BinarySearchTree<T>::preOrder(f1Typ f1, nodeType<T>* node) const
{
    if (node != nullptr)
    {
        (*f1)(node->data);
        preOrder(f1, node->left);
        preOrder(f1, node->right);
    }
}

template <class T>
void BinarySearchTree<T>::postOrderTraversal(f1Typ f1) const
{
    postOrder(f1, root);
}

template <class T>
void BinarySearchTree<T>::postOrder(f1Typ f1, nodeType<T>* node) const
{
    if (node != nullptr)
    {
        postOrder(f1, node->left);
        postOrder(f1, node->right);
        (*f1)(node->data);
    }
}

#endif // BST_H
