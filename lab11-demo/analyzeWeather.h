#ifndef ANALYZE_WEATHER_H
#define ANALYZE_WEATHER_H

#include "vector.h"
#include "weatherRecord.h"
#include "map.h"
#include "bst.h"
#include <string>

/**
 * @file analyzeWeather.h
 * @brief Weather data analysis with BST and Map integration for Assignment 2
 * @author Dhruv Goswami
 * @date 20/06/2025
 */

/**
 * @class analyzeWeather
 * @brief Provides statistical analysis capabilities for weather data using BST and Map
 */
class analyzeWeather {
public:

    /**
     * @brief Constructor
     * @param records Reference to vector containing weather data
     */
    analyzeWeather(const Vector<WeatherRecord>& records);

    /**
     * @brief Calculates wind speed statistics for a specific month and year
     * @param month Month to analyze (1-12)
     * @param year Year to analyze
     * @param meanSpeed Output parameter for mean wind speed in km/h
     * @param stdev Output parameter for standard deviation in km/h
     * @param mad Output parameter for mean absolute deviation in km/h
     * @return true if data found and calculated, false if no data available
     */
    bool CalculateWindSpeedStats(int month, int year, float& meanSpeed, float& stdev, float& mad);

    /**
     * @brief Calculates temperature statistics for a specific month and year
     * @param month Month to analyze (1-12)
     * @param year Year to analyze
     * @param meanTemp Output parameter for mean temperature in °C
     * @param stdev Output parameter for standard deviation in °C
     * @param mad Output parameter for mean absolute deviation in °C
     * @return true if data found and calculated, false if no data available
     */
    bool calculateTemperatureStats(int month, int year, float& meanTemp, float& stdev, float& mad);

    /**
     * @brief Calculates total solar radiation for a specific month and year
     * @param month Month to analyze (1-12)
     * @param year Year to analyze
     * @param totalRadiation Output parameter for total radiation in kWh/m²
     * @return true if data found and calculated, false if no data available
     */
    bool calculateSolarRadiation(int month, int year, float& totalRadiation);

    /**
     * @brief Calculates Sample Pearson Correlation Coefficient between two weather parameters
     * @param month Month to analyze (1-12)
     * @param year Year to analyze
     * @param dataType1 First parameter type: "wind", "temp", or "solar"
     * @param dataType2 Second parameter type: "wind", "temp", or "solar"
     * @param correlation Output parameter for correlation coefficient (-1 to 1)
     * @return true if data found and calculated, false if no data available
     */
    bool calculatesPCC(int month, int year, const std::string& dataType1,
                       const std::string& dataType2, float& correlation);

    /**
     * @brief Checks if data exists for a specific month and year
     * @param month Month to check (1-12)
     * @param year Year to check
     * @return true if at least one record exists for the specified month/year
     */
    bool hasDataForMonth(int month, int year);

    /**
     * @brief Gets all available years in the dataset using BST for efficient storage
     * @param years Vector to store the unique years found
     */
    void getAvailableYears(Vector<int>& years);

private:
    const Vector<WeatherRecord>& weatherData;  // Reference to weather data
    Map<std::string, Vector<WeatherRecord>> monthlyDataMap;  // Custom Map for fast lookup
    BinarySearchTree<int> availableYears;  // BST for year organization

    /**
     * @brief Initializes the Map and BST with weather data for efficient access
     */
    void initializeDataStructures();

    /**
     * @brief Creates a key string for month/year combination
     * @param month Month (1-12)
     * @param year Year
     * @return Key string in format "MM/YYYY"
     */
    std::string createMonthYearKey(int month, int year);

    /**
     * @brief Filters records by month and year
     * @param month Month to filter by (1-12)
     * @param year Year to filter by
     * @param filteredRecords Output vector for matching records
     */
    void filterRecordsByMonth(int month, int year, Vector<WeatherRecord>& filteredRecords);

    /**
     * @brief Extracts specific weather parameter from records into float vector
     * @param records Input weather records
     * @param dataType Parameter type: "wind", "temp", or "solar"
     * @param values Output vector for parameter values
     * @param convertUnits Whether to convert units (wind: m/s to km/h, solar: W/m² to kWh/m²)
     */
    void extractWeatherParameter(const Vector<WeatherRecord>& records,
                                const std::string& dataType,
                                Vector<float>& values,
                                bool convertUnits = true);

    /**
     * @brief Converts wind speed from m/s to km/h
     * @param mps Wind speed in meters per second
     * @return Wind speed in kilometers per hour
     */
    float convertMpsToKmh(float mps);

    /**
     * @brief Converts solar radiation from W/m² to kWh/m²
     * @param wPerM2 Solar radiation in watts per square meter
     * @return Solar radiation in kilowatt-hours per square meter
     */
    float convertWm2ToKwhM2(float wPerM2);
};

#endif // ANALYZE_WEATHER_H
