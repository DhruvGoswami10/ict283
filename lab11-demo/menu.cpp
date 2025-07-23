/**
 * @file menu.cpp
 * @brief Implementation of menu system for Assignment 2
 * @author Dhruv Goswami
 * @date 20/06/2025
 */

#include "menu.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

Menu::Menu() {}

void Menu::displayMenu() {
    std::cout << "\n=======================================" << std::endl;
    std::cout << "    Weather Data Analysis Menu" << std::endl;
    std::cout << "=======================================" << std::endl;
    std::cout << "1. Analyze Wind Speed Statistics" << std::endl;
    std::cout << "2. Analyze Temperature Statistics" << std::endl;
    std::cout << "3. Analyze Solar Radiation Statistics" << std::endl;
    std::cout << "4. Export Data to CSV" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "=======================================" << std::endl;
}

int Menu::getMenuChoice() {
    int choice;
    std::cout << "Enter your choice (1-5): ";
    std::cin >> choice;
    return choice;
}

void Menu::processMenuChoice(int choice, analyzeWeather& analyzer) {
    switch (choice) {
        case 1:
            handleWindSpeedStats(analyzer);
            break;
        case 2:
            handleTemperatureStats(analyzer);
            break;
        case 3:
            handleSolarRadiationStats(analyzer);
            break;
        case 4:
            handleExportCSV(analyzer);
            break;
        case 5:
            std::cout << "Exiting the program. Thank you!" << std::endl;
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
    std::cout << "Enter year (e.g., 2015): ";
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

std::string Menu::getParameterType() {
    std::cout << "\nSelect parameter type:" << std::endl;
    std::cout << "1. Wind Speed" << std::endl;
    std::cout << "2. Temperature" << std::endl;
    std::cout << "3. Solar Radiation" << std::endl;
    std::cout << "Enter choice (1-3): ";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1: return "wind";
        case 2: return "temp";
        case 3: return "solar";
        default:
            std::cout << "Invalid choice, defaulting to wind speed." << std::endl;
            return "wind";
    }
}

void Menu::handleWindSpeedStats(analyzeWeather& analyzer) {
    int month = getMonth();
    int year = getYear();
    float meanSpeed, stdev, mad;

    if (analyzer.CalculateWindSpeedStats(month, year, meanSpeed, stdev, mad)) {
        std::cout << "\n--- Wind Speed Statistics ---" << std::endl;
        std::cout << "Month/Year: " << getMonthName(month) << " " << year << std::endl;
        std::cout << "Mean Speed: " << std::fixed << std::setprecision(2) << meanSpeed << " km/h" << std::endl;
        std::cout << "Standard Deviation: " << stdev << " km/h" << std::endl;
        std::cout << "Mean Absolute Deviation: " << mad << " km/h" << std::endl;
    } else {
        std::cout << "No data available for " << getMonthName(month) << " " << year << std::endl;
    }
}

void Menu::handleTemperatureStats(analyzeWeather& analyzer) {
    int month = getMonth();
    int year = getYear();
    float meanTemp, stdev, mad;

    if (analyzer.calculateTemperatureStats(month, year, meanTemp, stdev, mad)) {
        std::cout << "\n--- Temperature Statistics ---" << std::endl;
        std::cout << "Month/Year: " << getMonthName(month) << " " << year << std::endl;
        std::cout << "Mean Temperature: " << std::fixed << std::setprecision(2) << meanTemp << " °C" << std::endl;
        std::cout << "Standard Deviation: " << stdev << " °C" << std::endl;
        std::cout << "Mean Absolute Deviation: " << mad << " °C" << std::endl;
    } else {
        std::cout << "No data available for " << getMonthName(month) << " " << year << std::endl;
    }
}

void Menu::handleSolarRadiationStats(analyzeWeather& analyzer) {
    int month = getMonth();
    int year = getYear();

    // Calculate solar radiation total
    float totalRadiation;
    if (analyzer.calculateSolarRadiation(month, year, totalRadiation)) {
        std::cout << "\n--- Solar Radiation Statistics ---" << std::endl;
        std::cout << "Month/Year: " << getMonthName(month) << " " << year << std::endl;
        std::cout << "Total Solar Radiation: " << std::fixed << std::setprecision(2)
                  << totalRadiation << " kWh/m²" << std::endl;
    } else {
        std::cout << "No data available for " << getMonthName(month) << " " << year << std::endl;
        return;
    }

    // NEW: Calculate sPCC between two parameters
    std::cout << "\n--- Sample Pearson Correlation Coefficient (sPCC) ---" << std::endl;
    std::cout << "Calculate correlation between two weather parameters for "
              << getMonthName(month) << " " << year << std::endl;

    std::cout << "\nSelect first parameter:" << std::endl;
    std::string param1 = getParameterType();

    std::cout << "\nSelect second parameter:" << std::endl;
    std::string param2 = getParameterType();

    float correlation;
    if (analyzer.calculatesPCC(month, year, param1, param2, correlation)) {
        std::cout << "\nCorrelation between " << param1 << " and " << param2
                  << ": " << std::fixed << std::setprecision(4) << correlation << std::endl;

        // Interpret correlation strength
        std::cout << "Interpretation: ";
        if (std::abs(correlation) >= 0.8) {
            std::cout << "Strong correlation";
        } else if (std::abs(correlation) >= 0.5) {
            std::cout << "Moderate correlation";
        } else if (std::abs(correlation) >= 0.3) {
            std::cout << "Weak correlation";
        } else {
            std::cout << "Very weak/No correlation";
        }

        if (correlation > 0) {
            std::cout << " (Positive)" << std::endl;
        } else if (correlation < 0) {
            std::cout << " (Negative)" << std::endl;
        } else {
            std::cout << std::endl;
        }
    } else {
        std::cout << "Cannot calculate correlation - insufficient data." << std::endl;
    }
}

void Menu::handleExportCSV(analyzeWeather& analyzer) {
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
        if (analyzer.hasDataForMonth(month, year)) {
            hasAnyData = true;

            float meanSpeed, stdevSpeed, madSpeed;
            float meanTemp, stdevTemp, madTemp;
            float totalRadiation;

            bool hasWind = analyzer.CalculateWindSpeedStats(month, year, meanSpeed, stdevSpeed, madSpeed);
            bool hasTemp = analyzer.calculateTemperatureStats(month, year, meanTemp, stdevTemp, madTemp);
            bool hasRadiation = analyzer.calculateSolarRadiation(month, year, totalRadiation);

            outFile << getMonthName(month) << ",";

            // Wind Speed with stdev and MAD
            if (hasWind) {
                outFile << meanSpeed << "(" << stdevSpeed << ", " << madSpeed << "),";
            } else {
                outFile << ",";
            }

            // Temperature with stdev and MAD
            if (hasTemp) {
                outFile << meanTemp << "(" << stdevTemp << ", " << madTemp << "),";
            } else {
                outFile << ",";
            }

            // Solar Radiation
            if (hasRadiation) {
                outFile << totalRadiation;
            }
            outFile << std::endl;
        }
    }

    if (!hasAnyData) {
        outFile << "No data available for year " << year << std::endl;
    }

    outFile.close();
    std::cout << "\nData exported to WindTempSolar.csv successfully." << std::endl;
    std::cout << "Format: Month,Average Wind Speed(stdev, mad),Average Ambient Temperature(stdev, mad),Total Solar Radiation" << std::endl;
}
