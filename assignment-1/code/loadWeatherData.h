#ifndef LOAD_WEATHER_DATA_H
#define LOAD_WEATHER_DATA_H

#include "vector.h"
#include "weatherRecord.h"
#include <string>

/**
 * @file loadWeatherData.h
 * @brief Data loading and CSV parsing functionality
 * @author Dhruv Goswami
 * @date 20/06/2025
 */

 /**
 * @class loadWeatherData
 * @brief Handles loading and parsing of weather data from CSV files
 */
class loadWeatherData {
public:

    /**
     * @brief Default constructor
     */
    loadWeatherData();

    /**
     * @brief Loads weather data from a CSV file
     * @param filename Path to the CSV file to load
     * @param records Vector to store the loaded weather records
     * @return true if data loaded successfully, false on error
     */
    bool loadData(const std::string & filename, Vector<WeatherRecord> & records);

    /**
     * @brief Gets the data source filename from configuration file
     * @return Full path to the data file, or empty string on error
     */
    std::string getDataSourceFilename();

private:
    /**
     * @brief Finds the index of a column in the header row
     * @param headers Vector of header strings
     * @param targetHeader Name of the column to find
     * @return Index of the column, or -1 if not found
     */
    int findColumnIndex(const Vector<std::string> & headers, const std::string & targetHeader);

    /**
     * @brief Parses a CSV line into individual fields
     * @param line CSV line to parse
     * @param fields Vector to store the parsed fields
     */
    void parseCSVLine(const std::string & line, Vector<std::string> & fields);

    /**
     * @brief Checks if a value represents missing data
     * @param value String value to check
     * @return true if value is empty, "NA", or "N/A"
     */
    bool isMissingData(const std::string & value);

    /**
     * @brief Converts string to float value
     * @param str String to convert
     * @return Float value, or 0.0 if string is empty
     */
    float stringToFloat(const std::string & str);
};

#endif
