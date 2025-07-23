// Project 2: Date Tree - reads from CSV files listed in data_source.txt
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include "../Bst.h"
#include "date.h"

using namespace std;

int main() {
    Bst<Date> dateTree;
    set<string> uniqueDates; // To avoid duplicate dates

    ifstream infile("data/data_source.txt");
    if (!infile) {
        cout << "Error: Could not open data/data_source.txt" << endl;
        return 1;
    }

    string filename;
    while (getline(infile, filename)) {
        if (!filename.empty()) {
            // Open each CSV file
            string filepath = "data/" + filename;
            ifstream csvFile(filepath);
            if (!csvFile) {
                cout << "Warning: Could not open " << filepath << endl;
                continue;
            }

            cout << "Processing file: " << filename << endl;

            string line;
            bool isFirstLine = true;
            int lineCount = 0;

            while (getline(csvFile, line)) {
                if (isFirstLine) {
                    isFirstLine = false;
                    continue; // Skip header line
                }

                if (!line.empty()) {
                    // Parse CSV line to get WAST column (first column)
                    stringstream ss(line);
                    string wastValue;
                    getline(ss, wastValue, ',');

                    // Extract date from WAST timestamp (format: DD/MM/YYYY HH:MM)
                    if (wastValue.length() >= 10) {
                        string dateStr = wastValue.substr(0, 10); // Get DD/MM/YYYY part

                        // Only insert if we haven't seen this date before
                        if (uniqueDates.find(dateStr) == uniqueDates.end()) {
                            uniqueDates.insert(dateStr);
                            Date date(dateStr);
                            dateTree.insert(date);
                        }
                    }
                }
                lineCount++;
                if (lineCount % 10000 == 0) {
                    cout << "Processed " << lineCount << " lines..." << endl;
                }
            }
            csvFile.close();
            cout << "Finished processing " << filename << " (" << lineCount << " lines)" << endl;
        }
    }
    infile.close();

    cout << "\nTotal unique dates inserted: " << uniqueDates.size() << endl;
    cout << "\n=== BST Operations Demo ===" << endl;

    cout << "\nInorder traversal (sorted dates): " << endl;
    dateTree.inOrderTraversal();
    cout << endl;

    cout << "\nPreorder traversal: " << endl;
    dateTree.preOrderTraversal();
    cout << endl;

    cout << "\nPostorder traversal: " << endl;
    dateTree.postOrderTraversal();
    cout << endl;

    // Test search functionality
    cout << "\n=== Testing Search Functionality ===" << endl;
    Date testDate1("01/01/2010");
    Date testDate2("31/12/2016");
    Date testDate3("99/99/9999"); // Date that shouldn't exist

    cout << "Searching for " << testDate1 << ": ";
    if (dateTree.search(testDate1)) {
        cout << "Found!" << endl;
    } else {
        cout << "Not found." << endl;
    }

    cout << "Searching for " << testDate2 << ": ";
    if (dateTree.search(testDate2)) {
        cout << "Found!" << endl;
    } else {
        cout << "Not found." << endl;
    }

    cout << "Searching for " << testDate3 << ": ";
    if (dateTree.search(testDate3)) {
        cout << "Found!" << endl;
    } else {
        cout << "Not found." << endl;
    }

    return 0;
}
