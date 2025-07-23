#ifndef MENU_H
#define MENU_H

#include "analyzeWeather.h"
#include <string>

/**
 * @file menu.h
 * @brief Updated Menu system for Assignment 2 with sPCC and MAD support
 * @author Dhruv Goswami
 * @date 20/06/2025
 */

/**
 * @class Menu
 * @brief Provides interactive menu interface for weather data analysis
 *
 * Updated Menu Options for Assignment 2:
 * 1. Analyze Wind Speed Statistics
 * 2. Analyze Temperature Statistics
 * 3. Analyze Solar Radiation Statistics WITH sPCC
 * 4. Export Data to CSV WITH MAD calculations
 * 5. Exit
 */
class Menu {
public:
    /**
     * @brief Default constructor
     */
    Menu();

    /**
     * @brief Displays the main menu options
     */
    void displayMenu();

    /**
     * @brief Gets user's menu choice
     * @return Selected menu option (1-5)
     */
    int getMenuChoice();

    /**
     * @brief Processes the user's menu selection
     * @param choice Selected menu option (1-5)
     * @param analyzer Reference to analyzeWeather object for data processing
     */
    void processMenuChoice(int choice, analyzeWeather& analyzer);

private:
    /**
     * @brief Gets month input from user with validation
     * @return Month value (1-12)
     */
    int getMonth();

    /**
     * @brief Gets year input from user
     * @return Year value
     */
    int getYear();

    /**
     * @brief Converts month number to month name
     * @param month Month number (1-12)
     * @return Month name string (e.g., "January", "February")
     */
    std::string getMonthName(int month);

    /**
     * @brief Handles wind speed statistics analysis (Menu option 1)
     * @param analyzer Reference to analyzeWeather object
     */
    void handleWindSpeedStats(analyzeWeather& analyzer);

    /**
     * @brief Handles temperature statistics analysis (Menu option 2)
     * @param analyzer Reference to analyzeWeather object
     */
    void handleTemperatureStats(analyzeWeather& analyzer);

    /**
     * @brief Handles solar radiation analysis WITH sPCC (Menu option 3)
     * @param analyzer Reference to analyzeWeather object
     */
    void handleSolarRadiationStats(analyzeWeather& analyzer);

    /**
     * @brief Handles CSV export functionality WITH MAD (Menu option 4)
     * @param analyzer Reference to analyzeWeather object
     */
    void handleExportCSV(analyzeWeather& analyzer);

    /**
     * @brief Gets parameter type for sPCC calculation
     * @return Parameter type: "wind", "temp", or "solar"
     */
    std::string getParameterType();
};

#endif // MENU_H
