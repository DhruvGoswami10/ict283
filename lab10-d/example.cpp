#include "bst.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

// Function prototypes (following textbook Example 19-5)
void print(int& x);
void update(int& x);

int main()
{
    BinarySearchTree<int> treeRoot;  // Following textbook naming
    int num;

    cout << "Enter numbers ending with -999." << endl;
    cin >> num;

    while (num != -999)
    {
        treeRoot.insertElement(num);
        cin >> num;
    }

    cout << endl << "Tree nodes in inorder: ";
    treeRoot.inOrderTraversal(print);    // Using function pointer
    cout << endl;

    cout << "******* Update Nodes *******" << endl;
    treeRoot.inOrderTraversal(update);   // Using function pointer to modify

    cout << "Tree nodes in inorder after the update:" << endl;
    cout << " ";
    treeRoot.inOrderTraversal(print);    // Print updated values
    cout << endl;

    return 0;
}

// Function definitions (following textbook Example 19-5)
void print(int& x)
{
    cout << x << " ";
}

void update(int& x)
{
    x = 2 * x;    // Double the value as in textbook
}
