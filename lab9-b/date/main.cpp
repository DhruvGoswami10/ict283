// Project 3: Date Tree - reads from date.txt (unordered dates)
#include <iostream>
#include <fstream>
#include <string>
#include "../Bst.h"
#include "date.h"

using namespace std;

int main() {
    Bst<Date> dateTree;

    ifstream infile("date.txt");
    if (!infile) {
        cout << "Error: Could not open date.txt" << endl;
        return 1;
    }

    string dateStr;
    while (getline(infile, dateStr)) {
        if (!dateStr.empty()) {
            Date date(dateStr);
            dateTree.insert(date);
        }
    }
    infile.close();

    cout << "Inorder traversal: ";
    dateTree.inOrderTraversal();
    cout << endl;

    cout << "Preorder traversal: ";
    dateTree.preOrderTraversal();
    cout << endl;

    cout << "Postorder traversal: ";
    dateTree.postOrderTraversal();
    cout << endl;

    return 0;
}
