#include "menu.h"
#include <iostream>
#include <iomanip>
#include <fstream>

Menu::Menu() {}

void Menu::displayMenu() {
    std::cout << "Weather Data Analysis Menu" << std::endl;
    std::cout << "1. Analyze Wind Speed Statistics" << std::endl;
    std::cout << "2. Analyze Temperature Statistics" << std::endl;
    std::cout << "3. Analyze Solar Radiation Statistics" << std::endl;
    std::cout << "4. Export Data to CSV" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

int Menu::getMenuChoice() {
    int choice;
    std::cout << "Enter your choice (1-5): ";
    std::cin >> choice;
    return choice;
}

void Menu::processmenuChoice(int choice, analyzeWeather & analyzer) {
    switch (choice) {
        case 1:
            handelWindSpeedStats(analyzer);
            break;
        case 2:
            handelTemperatureStats(analyzer);
            break;
        case 3:
            handelSolarRadiationStats(analyzer);
            break;
        case 4:
            handleExportCSV(analyzer);
            break;
        case 5:
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

int Menu::getMonth() {
    int month;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;
    while (month < 1 || month > 12) {
        std::cout << "Invalid month. Please enter a valid month (1-12): ";
        std::cin >> month;
    }
    return month;
}

int Menu::getYear() {
    int year;
    std::cout << "Enter year (e.g., 2023): ";
    std::cin >> year;
    return year;
}

std::string Menu::getMonthName(int month) {
    const std::string monthNames[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    return monthNames[month - 1];
}

void Menu::handelWindSpeedStats(analyzeWeather & analyzer) {
    int month = getMonth();
    int year = getYear();
    float meanSpeed, stdev;

    if (analyzer.CalculateWindSpeedStats(month, year, meanSpeed, stdev)) {
        std::cout << "Wind Speed Statistics for " << getMonthName(month) << " " << year << ":" << std::endl;
        std::cout << "Mean Speed: " << std::fixed << std::setprecision(2) << meanSpeed << " km/h" << std::endl;
        std::cout << "Standard Deviation: " << stdev << " km/h" << std::endl;
    } else {
        std::cout << "No data available for the specified month and year." << std::endl;
    }
}

void Menu::handelTemperatureStats(analyzeWeather & analyzer) {
    int month = getMonth();
    int year = getYear();
    float meanTemp, stdev;

    if (analyzer.calculateTemperatureStats(month, year, meanTemp, stdev)) {
        std::cout << "Temperature Statistics for " << getMonthName(month) << " " << year << ":" << std::endl;
        std::cout << "Mean Temperature: " << std::fixed << std::setprecision(2) << meanTemp << " °C" << std::endl;
        std::cout << "Standard Deviation: " << stdev << " °C" << std::endl;
    } else {
        std::cout << "No data available for the specified month and year." << std::endl;
    }
}

void Menu::handelSolarRadiationStats(analyzeWeather & analyzer) {
    int month = getMonth();
    int year = getYear();
    float totalRadiation;

    if (analyzer.calculateSOlarRadiation(month, year, totalRadiation)) {
        std::cout << "Total Solar Radiation for " << getMonthName(month) << " " << year << ": "
                  << std::fixed << std::setprecision(2) << totalRadiation << " kWh/m²" << std::endl;
    } else {
        std::cout << "No data available for the specified month and year." << std::endl;
    }
}

void Menu::handleExportCSV(analyzeWeather & analyzer) {
    int year = getYear();

    std::ofstream outFile("WindTempSolar.csv");
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    outFile << std::fixed << std::setprecision(2);
    outFile << year << std::endl;

    bool hasAnyData = false;
    for (int month = 1; month <= 12; ++month) {
        if (analyzer.hasDateForMonth(month, year)) {
            hasAnyData = true;
            float meanSpeed, stdevSpeed, meanTemp, stdevTemp, totalRadiation;
            bool hasWind = analyzer.CalculateWindSpeedStats(month, year, meanSpeed, stdevSpeed);
            bool hasTemp = analyzer.calculateTemperatureStats(month, year, meanTemp, stdevTemp);
            bool hasRadiation = analyzer.calculateSOlarRadiation(month, year, totalRadiation);

            outFile << getMonthName(month) << ",";

            if (hasWind) {
                outFile << meanSpeed << "," << stdevSpeed << ",";
            } 
            outFile << ",";

            if (hasTemp) {
                outFile << meanTemp << "(" << stdevTemp << ")";
            }
            outFile << ",";

            if (hasRadiation) {
                outFile << totalRadiation;
            }
            outFile << std::endl;
        }
    }

    if (!hasAnyData){
        outFile << "No Data mate" << std::endl;
    }

    outFile.close();
    std::cout << "Data exported to WindTempSolar.csv successfully." << std::endl;
}