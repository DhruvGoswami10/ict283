#ifndef ANALYZE_WEATHER_H
#define ANALYZE_WEATHER_H

#include "vector.h"
#include "weatherRecord.h"
#include <string>

/**
 * @file analyzeWeather.h
 * @brief Data loading and CSV parsing functionality
 * @author Dhruv Goswami
 * @date 20/06/2025
 */

 /**
 * @class analyzeWeather
 * @brief Provides statistical analysis capabilities for weather data
 */
class analyzeWeather {
public:

    /**
     * @brief Constructor
     * @param records Reference to vector containing weather data
     */
    analyzeWeather(const Vector<WeatherRecord> & records);

    /**
     * @brief Calculates wind speed statistics for a specific month and year
     * @param month Month to analyze (1-12)
     * @param year Year to analyze
     * @param meanSpeed Output parameter for mean wind speed in km/h
     * @param stdev Output parameter for standard deviation in km/h
     * @return true if data found and calculated, false if no data available
     */
    bool CalculateWindSpeedStats(int month, int year, float & meanSpeed, float & stdev);

    /**
     * @brief Calculates temperature statistics for a specific month and year
     * @param month Month to analyze (1-12)
     * @param year Year to analyze
     * @param meanTemp Output parameter for mean temperature in °C
     * @param stdev Output parameter for standard deviation in °C
     * @return true if data found and calculated, false if no data available
     */
    bool calculateTemperatureStats(int month, int year, float & meanTemp, float & stdev);

    /**
     * @brief Calculates total solar radiation for a specific month and year
     * @param month Month to analyze (1-12)
     * @param year Year to analyze
     * @param totalRadiation Output parameter for total radiation in kWh/m²
     * @return true if data found and calculated, false if no data available
     */
    bool calculateSOlarRadiation(int month, int year, float & totalRadiation);

    /**
     * @brief Checks if data exists for a specific month and year
     * @param month Month to check (1-12)
     * @param year Year to check
     * @return true if at least one record exists for the specified month/year
     */
    bool hasDateForMonth(int month, int year);

    /**
     * @brief Gets all available years in the dataset
     * @param years Vector to store the unique years found
     */
    void getAvailableYears(Vector<int> & years);

private:
    const Vector<WeatherRecord> & weatherData;  //reference to weather data

    /**
     * @brief Filters records by month and year
     * @param month Month to filter by (1-12)
     * @param year Year to filter by
     * @param filteredRecords Output vector for matching records
     */
    void filterRecordsByMonth(int month, int year, Vector<WeatherRecord> & filteredRecords);

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

#endif
