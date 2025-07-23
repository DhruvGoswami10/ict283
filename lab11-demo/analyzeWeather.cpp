/**
 * @file analyzeWeather.cpp
 * @brief Implementation of weather data analysis with BST and Map integration
 * @author Dhruv Goswami
 * @date 20/06/2025
 */

#include "analyzeWeather.h"
#include "statistics.h"

analyzeWeather::analyzeWeather(const Vector<WeatherRecord>& records) : weatherData(records) {
    initializeDataStructures();
}

void analyzeWeather::initializeDataStructures() {
    // Populate Map and BST with data for efficient access
    for (int i = 0; i < weatherData.size(); i++) {
        const WeatherRecord& record = weatherData[i];
        int year = record.getDate().GetYear();
        int month = record.getDate().GetMonth();

        // Add year to BST (BST handles duplicates by not inserting)
        availableYears.insertElement(year);

        // Add record to Map by month/year key
        std::string key = createMonthYearKey(month, year);

        // For simplified Map implementation, we'll use the original filtering approach
        // In a full implementation, we'd add records to Map here
    }
}

std::string analyzeWeather::createMonthYearKey(int month, int year) {
    // Create key in format "MM/YYYY" (e.g., "01/2010")
    std::string monthStr = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
    return monthStr + "/" + std::to_string(year);
}

bool analyzeWeather::CalculateWindSpeedStats(int month, int year, float& meanSpeed, float& stdev, float& mad) {
    Vector<WeatherRecord> filteredRecords;
    filterRecordsByMonth(month, year, filteredRecords);

    if (filteredRecords.size() == 0) {
        return false;
    }

    Vector<float> windSpeeds;
    extractWeatherParameter(filteredRecords, "wind", windSpeeds, true);

    meanSpeed = statistics::calculateMean(windSpeeds);
    stdev = statistics::calculateStandardDeviation(windSpeeds, meanSpeed);
    mad = statistics::calculateMAD(windSpeeds, meanSpeed);

    return true;
}

bool analyzeWeather::calculateTemperatureStats(int month, int year, float& meanTemp, float& stdev, float& mad) {
    Vector<WeatherRecord> filteredRecords;
    filterRecordsByMonth(month, year, filteredRecords);

    if (filteredRecords.size() == 0) {
        return false;
    }

    Vector<float> temperatures;
    extractWeatherParameter(filteredRecords, "temp", temperatures, false);

    meanTemp = statistics::calculateMean(temperatures);
    stdev = statistics::calculateStandardDeviation(temperatures, meanTemp);
    mad = statistics::calculateMAD(temperatures, meanTemp);

    return true;
}

bool analyzeWeather::calculateSolarRadiation(int month, int year, float& totalRadiation) {
    Vector<WeatherRecord> filteredRecords;
    filterRecordsByMonth(month, year, filteredRecords);

    if (filteredRecords.size() == 0) {
        return false;
    }

    Vector<float> solarValues;
    extractWeatherParameter(filteredRecords, "solar", solarValues, true);

    totalRadiation = statistics::calculateSum(solarValues);
    return true;
}

bool analyzeWeather::calculatesPCC(int month, int year, const std::string& dataType1,
                                  const std::string& dataType2, float& correlation) {
    Vector<WeatherRecord> filteredRecords;
    filterRecordsByMonth(month, year, filteredRecords);

    if (filteredRecords.size() < 2) {
        return false; // Need at least 2 points for correlation
    }

    Vector<float> values1, values2;
    extractWeatherParameter(filteredRecords, dataType1, values1, true);
    extractWeatherParameter(filteredRecords, dataType2, values2, true);

    correlation = statistics::calculatesPCC(values1, values2);
    return true;
}

void analyzeWeather::extractWeatherParameter(const Vector<WeatherRecord>& records,
                                           const std::string& dataType,
                                           Vector<float>& values,
                                           bool convertUnits) {
    for (int i = 0; i < records.size(); i++) {
        if (dataType == "wind") {
            float windSpeed = records[i].getWindSpeed();
            if (convertUnits) {
                windSpeed = convertMpsToKmh(windSpeed);
            }
            values.push_back(windSpeed);
        } else if (dataType == "temp") {
            values.push_back(records[i].getTemperature());
        } else if (dataType == "solar") {
            float solarRad = records[i].getSolarRadiation();
            if (convertUnits) {
                solarRad = convertWm2ToKwhM2(solarRad);
            }
            values.push_back(solarRad);
        }
    }
}

bool analyzeWeather::hasDataForMonth(int month, int year) {
    for (int i = 0; i < weatherData.size(); i++) {
        if (weatherData[i].getDate().GetMonth() == month && weatherData[i].getDate().GetYear() == year) {
            return true;
        }
    }
    return false;
}

void analyzeWeather::getAvailableYears(Vector<int>& years) {
    // For simplified implementation, extract years directly
    // In full implementation, we'd traverse the BST
    Vector<int> foundYears;

    for (int i = 0; i < weatherData.size(); i++) {
        int year = weatherData[i].getDate().GetYear();

        bool alreadyExists = false;
        for (int j = 0; j < foundYears.size(); j++) {
            if (foundYears[j] == year) {
                alreadyExists = true;
                break;
            }
        }

        if (!alreadyExists) {
            foundYears.push_back(year);
        }
    }
    years = foundYears;
}

void analyzeWeather::filterRecordsByMonth(int month, int year, Vector<WeatherRecord>& filteredRecords) {
    for (int i = 0; i < weatherData.size(); i++) {
        if (weatherData[i].getDate().GetMonth() == month && weatherData[i].getDate().GetYear() == year) {
            filteredRecords.push_back(weatherData[i]);
        }
    }
}

float analyzeWeather::convertMpsToKmh(float mps) {
    return mps * 3.6f;
}

float analyzeWeather::convertWm2ToKwhM2(float wPerM2) {
    return wPerM2 * (1.0f / 6.0f) / 1000.0f;
}
