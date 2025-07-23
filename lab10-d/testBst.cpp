#include "bst.h"
#include <iostream>
#include <vector>

// Namespace usage - don't expose entire std namespace
using std::cout;
using std::endl;
using std::vector;

// Forward declarations
void testBasicOperations();
void testFunctionPointers();
void testPassingMethods();
void testWithCustomClass();

// Function pointer callback functions for testing (following textbook style)
void print(int& value);        // Print function - textbook Example 19-5 style
void update(int& value);       // Update function - textbook Example 19-5 style
void printString(std::string& value);

// Test functions for passing BST by different methods
void testPassByValue(BinarySearchTree<int> tree);
void testPassByConstReference(const BinarySearchTree<int>& tree);
void testPassByReference(BinarySearchTree<int>& tree);

// Custom class for testing BST requirements
class TestData
{
private:
    int value;
    static int counter;

public:
    TestData() : value(++counter) {}
    TestData(int val) : value(val) {}

    int getValue() const { return value; }

    // Required operators for BST operations
    bool operator<(const TestData& other) const { return value < other.value; }
    bool operator>(const TestData& other) const { return value > other.value; }
    bool operator==(const TestData& other) const { return value == other.value; }

    // For printing
    friend std::ostream& operator<<(std::ostream& os, const TestData& data)
    {
        os << data.value;
        return os;
    }
};

int TestData::counter = 0;

// Callback function for TestData
void printTestData(TestData& data);

int main()
{
    cout << "=== Binary Search Tree Lab 10 Exercise d Test Program ===" << endl << endl;

    testBasicOperations();
    testFunctionPointers();
    testPassingMethods();
    testWithCustomClass();

    cout << "=== All tests completed successfully! ===" << endl;
    return 0;
}

void testBasicOperations()
{
    cout << "1. Testing Basic BST Operations:" << endl;
    cout << "--------------------------------" << endl;

    BinarySearchTree<int> intTree;

    // Test empty tree
    cout << "Empty tree: " << (intTree.isEmpty() ? "Yes" : "No") << endl;

    // Insert elements
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int numValues = sizeof(values) / sizeof(values[0]);

    cout << "Inserting values: ";
    for (int i = 0; i < numValues; i++)
    {
        cout << values[i] << " ";
        intTree.insertElement(values[i]);
    }
    cout << endl;

    // Test search
    cout << "Tree empty after insertion: " << (intTree.isEmpty() ? "Yes" : "No") << endl;
    cout << "Search for 40: " << (intTree.searchElement(40) ? "Found" : "Not Found") << endl;
    cout << "Search for 100: " << (intTree.searchElement(100) ? "Found" : "Not Found") << endl;

    cout << endl;
}

void testFunctionPointers()
{
    cout << "2. Testing Function Pointers in Traversals:" << endl;
    cout << "------------------------------------------" << endl;

    BinarySearchTree<int> intTree;

    // Insert test data
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++)
    {
        intTree.insertElement(values[i]);
    }

    cout << "Original tree (in-order): ";
    intTree.inOrderTraversal(print);
    cout << endl;

    cout << "Pre-order traversal: ";
    intTree.preOrderTraversal(print);
    cout << endl;

    cout << "Post-order traversal: ";
    intTree.postOrderTraversal(print);
    cout << endl;

    // Test modifying data through function pointer (following textbook example)
    BinarySearchTree<int> modifyTree;
    int smallValues[] = {5, 3, 7, 2, 4};
    for (int i = 0; i < 5; i++)
    {
        modifyTree.insertElement(smallValues[i]);
    }

    cout << "Before updating (in-order): ";
    modifyTree.inOrderTraversal(print);
    cout << endl;

    cout << "Updating all values..." << endl;
    modifyTree.inOrderTraversal(update);     // Using update function like textbook

    cout << "After updating (in-order): ";
    modifyTree.inOrderTraversal(print);
    cout << endl;

    cout << endl;
}

void testPassingMethods()
{
    cout << "3. Testing BST Passing by Value, Reference, and Const Reference:" << endl;
    cout << "----------------------------------------------------------------" << endl;

    BinarySearchTree<int> originalTree;

    // Insert test data
    int values[] = {50, 30, 70, 20, 40};
    for (int i = 0; i < 5; i++)
    {
        originalTree.insertElement(values[i]);
    }

    cout << "Original tree: ";
    originalTree.inOrderTraversal(print);
    cout << endl;

    // Test pass by value
    cout << "Testing pass by value..." << endl;
    testPassByValue(originalTree);

    cout << "Original tree after pass by value: ";
    originalTree.inOrderTraversal(print);
    cout << endl;

    // Test pass by const reference
    cout << "Testing pass by const reference..." << endl;
    testPassByConstReference(originalTree);

    // Test pass by reference
    cout << "Testing pass by reference..." << endl;
    testPassByReference(originalTree);

    cout << "Original tree after pass by reference: ";
    originalTree.inOrderTraversal(print);
    cout << endl;

    cout << endl;
}

void testWithCustomClass()
{
    cout << "4. Testing BST with Custom Class:" << endl;
    cout << "---------------------------------" << endl;

    BinarySearchTree<TestData> dataTree;

    // Insert TestData objects
    for (int i = 0; i < 5; i++)
    {
        TestData data(10 + i * 5);
        dataTree.insertElement(data);
    }

    cout << "Custom class tree (in-order): ";
    dataTree.inOrderTraversal(printTestData);
    cout << endl;

    // Test search
    TestData searchData(15);
    cout << "Search for value 15: " << (dataTree.searchElement(searchData) ? "Found" : "Not Found") << endl;

    TestData searchData2(100);
    cout << "Search for value 100: " << (dataTree.searchElement(searchData2) ? "Found" : "Not Found") << endl;

    cout << endl;
}

// Function pointer implementations (following textbook Example 19-5 style)
void print(int& value)
{
    cout << value << " ";
}

void update(int& value)
{
    value = 2 * value;          // Double the value like textbook example
}

void printString(std::string& value)
{
    cout << value << " ";
}

void printTestData(TestData& data)
{
    cout << data << " ";
}

// Test functions for different passing methods
void testPassByValue(BinarySearchTree<int> tree)
{
    cout << "  Inside pass by value function: ";
    tree.inOrderTraversal(print);
    cout << endl;

    // Insert new element to verify it's a copy
    tree.insertElement(100);
    cout << "  After inserting 100 in copy: ";
    tree.inOrderTraversal(print);
    cout << endl;
}

void testPassByConstReference(const BinarySearchTree<int>& tree)
{
    cout << "  Inside pass by const reference function: ";
    tree.inOrderTraversal(print);
    cout << endl;

    // Cannot modify const reference - this would cause compile error:
    // tree.insertElement(200);
}

void testPassByReference(BinarySearchTree<int>& tree)
{
    cout << "  Inside pass by reference function: ";
    tree.inOrderTraversal(print);
    cout << endl;

    // Insert new element to verify it modifies original
    tree.insertElement(200);
    cout << "  After inserting 200 in reference: ";
    tree.inOrderTraversal(print);
    cout << endl;
}
