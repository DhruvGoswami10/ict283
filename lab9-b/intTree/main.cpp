// Project 1: Integer Tree - reads from integers.txt
#include <iostream>
#include <fstream>
#include "../Bst.h"

using namespace std;

int main() {
    Bst<int> intTree;

    ifstream infile("int.txt");
    if (!infile) {
        cout << "Error: Could not open integers.txt" << endl;
        return 1;
    }

    int value;
    while (infile >> value) {
        intTree.insert(value);
    }
    infile.close();

    cout << "Inorder traversal: ";
    intTree.inOrderTraversal();
    cout << endl;

    cout << "Preorder traversal: ";
    intTree.preOrderTraversal();
    cout << endl;

    cout << "Postorder traversal: ";
    intTree.postOrderTraversal();
    cout << endl;

    return 0;
}
