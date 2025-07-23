/**
 * @file main.cpp
 * @brief Data loading and CSV parsing functionality
 * @author Dhruv Goswami
 * @date 20/06/2025
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
 * Program flow:
 * 1. Load data source configuration
 * 2. Load and parse weather data from CSV
 * 3. Initialize analysis and menu systems
 * 4. Run interactive menu loop until user exits
 */
int main(){
    std::cout << "Weather Data Analysis Program" << std::endl;
    std::cout << "Loading data..." << std::endl;

    loadWeatherData dataLoader;
    std::string dataFile = dataLoader.getDataSourceFilename();

    if (dataFile.empty()) {
        std::cerr << "Failed to load data source filename." << std::endl;
        return 1;
    }

    Vector<WeatherRecord> records;
    if (!dataLoader.loadData(dataFile, records)) {
        std::cerr << "Failed to load weather data from " << dataFile << std::endl;
        return 1;
    }

    std::cout << "Data loaded successfully. Number of records: " << records.size() << std::endl;

    analyzeWeather analyzer(records);
    Menu menu;

    int choice;
    do {
        menu.displayMenu();
        choice = menu.getMenuChoice();
        menu.processmenuChoice(choice, analyzer);
    } while (choice != 5);

    return 0;
}
