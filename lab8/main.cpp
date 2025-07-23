/**
 * @file main.cpp
 * @brief Data loading and CSV parsing functionality - Modified for Lab 8 Question 4
 * @author Dhruv Goswami
 * @date 4/07/2025
 */

#include <iostream>
#include "vector.h"
#include "weatherRecord.h"
#include "loadWeatherData.h"
#include "analyzeWeather.h"
#include "menu.h"

/**
 * @brief Main function - entry point for the application
 * @return 0 on success, 1 on error
 *
 * Program flow (Lab 8 - Multiple File Version):
 * 1. Load ALL data files listed in data_source.txt
 * 2. Load and parse weather data from ALL CSV files
 * 3. Initialize analysis and menu systems with combined data
 * 4. Run interactive menu loop until user exits
 */
int main(){
    std::cout << "Weather Data Analysis Program" << std::endl;
    std::cout << "Loading data from multiple files..." << std::endl;

    loadWeatherData dataLoader;
    Vector<WeatherRecord> records;

    // NEW: Load from ALL files instead of just one
    if (!dataLoader.loadAllDataFiles(records)) {
        std::cerr << "Failed to load weather data from any files." << std::endl;
        return 1;
    }

    std::cout << "Data loaded successfully. Total records: " << records.size() << std::endl;

    // Display available years for user information
    analyzeWeather analyzer(records);
    Vector<int> availableYears;
    analyzer.getAvailableYears(availableYears);
    
    std::cout << "Available years in dataset: ";
    for (int i = 0; i < availableYears.size(); i++) {
        std::cout << availableYears[i];
        if (i < availableYears.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl << std::endl;

    Menu menu;

    int choice;
    do {
        menu.displayMenu();
        choice = menu.getMenuChoice();
        menu.processmenuChoice(choice, analyzer);
    } while (choice != 5);

    return 0;
}