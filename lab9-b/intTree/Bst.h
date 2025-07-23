#ifndef BST_H
#define BST_H

#include <iostream>

template <class T>
class Node{
public:
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <class T>
class Bst{
private:
    Node<T>* root;

    Node<T>* insertRecursive(Node<T>* node, const T& value);
    bool searchRecursive(Node<T>* node, const T& value) const;
    void inOrderRecursive(Node<T>* node) const;
    void preOrderRecursive(Node<T>* node) const;
    void postOrderRecursive(Node<T>* node) const;
    void deleteTreeRecursive(Node<T>* node);
    Node<T>* copyTreeRecursive(Node<T>* node);

public:
    // Constructors and destructor
    Bst();
    ~Bst();
    Bst(const Bst<T>& other);
    Bst<T>& operator=(const Bst<T>& other);

    void insert(const T& value);
    bool search(const T& value) const;
    void inOrderTraversal() const;
    void preOrderTraversal() const;
    void postOrderTraversal() const;
    void deleteTree();
    bool isEmpty() const;
};

// Implementation

template <class T>
Bst<T>::Bst() : root(nullptr) {}

template <class T>
Bst<T>::~Bst() {
    deleteTree();
}

template <class T>
Bst<T>::Bst(const Bst<T>& other) : root(nullptr){
    root = copyTreeRecursive(other.root);
}

template <class T>
Bst<T>& Bst<T>::operator=(const Bst<T>& other){
    if (this != &other) {
        deleteTree();
        root = copyTreeRecursive(other.root);
    }
    return *this;
}

template <class T>
Node<T>* Bst<T>::copyTreeRecursive(Node<T>* node) {
    if (node == nullptr) {
        return nullptr;
    }

    Node<T>* newNode = new Node<T>(node->data);
    newNode->left = copyTreeRecursive(node->left);
    newNode->right = copyTreeRecursive(node->right);
    return newNode;
}

template <class T>
void Bst<T>::insert(const T& value){
    root = insertRecursive(root, value);
}

template <class T>
Node<T>* Bst<T>::insertRecursive(Node<T>* node, const T& value){
    if (node == nullptr) {
        return new Node<T>(value);
    }

    if (value < node->data){
        node->left = insertRecursive(node->left, value);
    } else if (value > node->data){
        node->right = insertRecursive(node->right, value);
    }

    return node;
}

template <class T>
bool Bst<T>::search(const T& value) const{
    return searchRecursive(root, value);
}

template <class T>
bool Bst<T>::searchRecursive(Node<T>* node, const T& value) const {
    if (node == nullptr){
        return false;
    }

    if (value == node->data){
        return true;
    }

    if (value < node->data){
        return searchRecursive(node->left, value);
    } else {
        return searchRecursive(node->right, value);
    }
}

template <class T>
void Bst<T>::inOrderTraversal() const{
    inOrderRecursive(root);
}

template <class T>
void Bst<T>::inOrderRecursive(Node<T>* node) const{
    if (node != nullptr){
        inOrderRecursive(node->left);
        std::cout << node->data << " ";
        inOrderRecursive(node->right);
    }
}

template <class T>
void Bst<T>::preOrderTraversal() const{
    preOrderRecursive(root);
}

template <class T>
void Bst<T>::preOrderRecursive(Node<T>* node) const {
    if (node != nullptr){
        std::cout << node->data << " ";
        preOrderRecursive(node->left);
        preOrderRecursive(node->right);
    }
}

template <class T>
void Bst<T>::postOrderTraversal() const {
    postOrderRecursive(root);
}

template <class T>
void Bst<T>::postOrderRecursive(Node<T>* node) const {
    if (node != nullptr){
        postOrderRecursive(node->left);
        postOrderRecursive(node->right);
        std::cout << node->data << " ";
    }
}

template <class T>
void Bst<T>::deleteTree(){
    deleteTreeRecursive(root);
    root = nullptr;
}

template <class T>
void Bst<T>::deleteTreeRecursive(Node<T>* node){
    if (node != nullptr){
        deleteTreeRecursive(node->left);
        deleteTreeRecursive(node->right);
        delete node;
    }
}

template <class T>
bool Bst<T>::isEmpty() const {
    return root == nullptr;
}

#endif