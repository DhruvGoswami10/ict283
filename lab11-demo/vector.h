#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

/**
 * @class Vector
 * @brief Template based dynamic array implementation
 * 
 * A custom vector class that provides dynamic array functionality without using STL containers
 * Since it is dynamic array it supports automatic resizing and basic array operations.alignas
 * 
 * @author Dhruv Goswami
 * @version 1.0
 * @date 19-06-2025
 */

template <class T>
class Vector {
public:
    /**
     * @brief Default constructor
     * @param size initial capacity of the vector
     */
    Vector(int size = 10);

    /**
     * @brief Copy constructor
     * @param other the vector to copy from
     */
    Vector(const Vector & other);

    /**
     * @brief Destructor
     */
    ~Vector();

    /**
     * @brief Assignment operator
     * @param other the vector to assign from
     * @return reference to the current vector
     */
    Vector & operator=(const Vector & other);

    /**
     * @brief Returns the number of elements in the vector
     * @return the current size of the vector
     */
    int size() const;

    /**
     * @brief Adds a new element to the end of the vector
     * @param value the value to add
     */
    void push_back(const T & value);

    /**
     * @brief Accesses an element at a specific index
     * @param index the index of the element to access
     * @return reference to the element at the specified index
     */
    T & operator[](int index);

    /**
     * @brief Accesses an element at a specific index (const version)
     * @param index the index of the element to access
     * @return const reference to the element at the specified index
     */
    const T & operator[](int index) const;

private:
    T * data;       // Pointer to the array that holds the elements
    int count;      // Current number of elements in the vector
    int capacity;   // Max capacity before resizing

    void resize();
};

// Implementation

template <class T>
Vector<T>::Vector(int size) : count(0), capacity(size) {
    data = new T[capacity];
}// Constructor


template <class T>
Vector<T>::Vector(const Vector<T> & other) : count(other.count), capacity(other.capacity) {
    data = new T[capacity];
    for (int i = 0; i < count; i++) {
        data[i] = other.data[i];
    }
}// Copy constructor

template <class T> 
Vector<T>::~Vector() {
    delete[] data;
}// Destructor

template <class T>
Vector<T> & Vector<T>::operator=(const Vector<T> & other) {
    if (this != &other) {
        delete[] data;
        count = other.count;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}// Assignment operator

template <class T>
int Vector<T>::size() const {
    return count;
}// Returns the number of elements in the vector

template <class T>
void Vector<T>::push_back(const T & value) {
    if (count == capacity) {
        resize();
    }
    data[count++] = value;
}// Adds a new element to the end of the vector

template <class T>
T & Vector<T>::operator[](int index) {
    assert(index >= 0 && index < count);
    return data[index];
}// Accesses an element at a specific index (non-const version)

template <class T>
const T & Vector<T>::operator[](int index) const {
    assert(index >= 0 && index < count);
    return data[index];
}// Accesses an element at a specific index (const version)

template <class T>
void Vector<T>::resize() {
    capacity *= 2;
    T * newData = new T[capacity];
    for (int i = 0; i < count; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}// Resizes the vector to double its current capacity

#endif