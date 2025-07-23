/**
 * @file main.cpp
 * @brief Assignment 2 Main Program with BST, Map, sPCC, and MAD
 * @author Dhruv Goswami
 * @date 20/06/2025
 *
 * Features:
 * - Custom Map class for 10% bonus (minimal but complete - 4 methods)
 * - Minimal BST implementation (no isEmpty, height, etc.)
 * - sPCC (Sample Pearson Correlation Coefficient) in Menu Option 3
 * - MAD (Mean Absolute Deviation) in Menu Option 4
 * - Math/stats functions NOT coupled to weather data types
 * - Updated CSV export format with (stdev, mad) notation
 */

#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "weatherRecord.h"
#include "loadWeatherData.h"
#include "analyzeWeather.h"
#include "menu.h"
#include "Map.h"
#include "bst.h"
#include "statistics.h"

/**
 * @brief Main function - entry point for Assignment 2
 * @return 0 on success, 1 on error
 *
 * Program flow:
 * 1. Load data source configuration
 * 2. Load and parse weather data from multiple CSV files (14 files)
 * 3. Initialize analysis system with BST and Map integration
 * 4. Run interactive menu loop with updated Assignment 2 features
 */
int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "     Weather Data Analysis Program - Assignment 2" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "Features: Custom Map, Minimal BST, sPCC, MAD" << std::endl;
    std::cout << "Loading data..." << std::endl;

    loadWeatherData dataLoader;
    std::string dataFile = dataLoader.getDataSourceFilename();

    if (dataFile.empty()) {
        std::cerr << "Failed to load data source filename." << std::endl;
        return 1;
    }

    Vector<WeatherRecord> allRecords;

    // Load multiple data files as specified in data_source.txt
    std::ifstream sourceFile("data/data_source.txt");
    if (!sourceFile) {
        std::cerr << "Cannot open data_source.txt" << std::endl;
        return 1;
    }

    std::string filename;
    int filesLoaded = 0;
    while (std::getline(sourceFile, filename)) {
        std::string fullPath = "data/" + filename;
        Vector<WeatherRecord> records;

        if (dataLoader.loadData(fullPath, records)) {
            std::cout << "Loaded " << records.size() << " records from " << filename << std::endl;

            // Merge records into allRecords
            for (int i = 0; i < records.size(); i++) {
                allRecords.push_back(records[i]);
            }
            filesLoaded++;
        } else {
            std::cout << "Warning: Could not load " << fullPath << std::endl;
        }
    }
    sourceFile.close();

    if (allRecords.size() == 0) {
        std::cerr << "No data loaded from any files." << std::endl;
        return 1;
    }

    std::cout << "\nData loading complete!" << std::endl;
    std::cout << "Files loaded: " << filesLoaded << std::endl;
    std::cout << "Total records: " << allRecords.size() << std::endl;

    // Demonstrate custom Map class usage (for bonus marks)
    std::cout << "\n--- Custom Map Class Demo ---" << std::endl;
    Map<std::string, int> testMap;
    testMap.insert("2010", 1000);
    testMap.insert("2011", 2000);

    if (testMap.find("2010")) {
        std::cout << "Map working: Found key '2010'" << std::endl;
    }

    // Demonstrate minimal BST usage
    std::cout << "\n--- Minimal BST Demo ---" << std::endl;
    BinarySearchTree<int> yearTree;
    yearTree.insertElement(2010);
    yearTree.insertElement(2011);
    yearTree.insertElement(2015);

    if (yearTree.searchElement(2010)) {
        std::cout << "BST working: Found year 2010" << std::endl;
    }

    // Initialize analyzer with BST and Map integration
    analyzeWeather analyzer(allRecords);
    Menu menu;

    int choice;
    do {
        menu.displayMenu();
        choice = menu.getMenuChoice();

        if (choice != 5) {
            menu.processMenuChoice(choice, analyzer);

            // Pause for user to read output
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    } while (choice != 5);

    std::cout << "\nProgram terminated successfully." << std::endl;
    return 0;
}

/**
 * Assignment 2 Implementation Notes:
 *
 * 1. MINIMAL BST (bst.h):
 *    - Only essential operations: insert, search, destroy, traversals
 *    - NO isEmpty(), height(), nodeCount() - these are NOT minimal
 *    - Function pointers for flexible traversals
 *    - Proper memory management
 *
 * 2. CUSTOM MAP CLASS (Map.h) - FOR 10% BONUS:
 *    - Exactly 4 public methods: insert(), operator[], find(), clear()
 *    - Uses BST internally for implementation
 *    - Minimal but complete - primary behavior is key-value association
 *    - NOT the same as std::map - our own minimal interface
 *
 * 3. sPCC (statistics.h):
 *    - Sample Pearson Correlation Coefficient
 *    - Integrated into Menu Option 3 (Solar Radiation Statistics)
 *    - NOT coupled to weather data types - works with any Vector<float>
 *
 * 4. MAD (statistics.h):
 *    - Mean Absolute Deviation
 *    - Integrated into Menu Option 4 (CSV Export)
 *    - Output format: Average(stdev, mad)
 *    - NOT coupled to weather data types
 *
 * 5. UPDATED MENU SYSTEM:
 *    - Menu Option 3: Solar Radiation + sPCC between any two parameters
 *    - Menu Option 4: CSV Export with MAD alongside standard deviation
 *    - Format: "Month,Average Wind Speed(stdev, mad),Average Ambient Temperature(stdev, mad),Total Solar Radiation"
 *
 * 6. NO COUPLING:
 *    - All math/stats functions work with Vector<float>
 *    - Can be reused with any numeric data, not just weather
 *    - Clean separation between data types and statistical operations
 *
 * 7. DATA HANDLING:
 *    - Loads all 14 data files from data_source.txt
 *    - Handles multiple years of weather data
 *    - BST used for year organization and efficient lookups
 *    - Map used for month/year data organization
 *
 * Ready for Lab 11 demonstration to tutor for assessment!
 */


 /**
 * MetData_Mar01-2015-Mar01-2016-ALL.csv
 * MetData_Jan01-2010-Jan01-2011-ALL.csv
 * MetData-31-3b.csv
 * MetData_Jan01-2011-Jan01-2012-ALL.csv
 * MetData-31-3c.csv
 * MetData_Mar01-2014-Mar01-2015-ALL.csv
 */
