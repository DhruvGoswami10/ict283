#include "analyzeWeather.h"
#include "statistics.h"

analyzeWeather::analyzeWeather(const Vector<WeatherRecord> & records) : weatherData(records) {}

bool analyzeWeather::CalculateWindSpeedStats(int month, int year, float & meanSpeed, float & stdev) {
    Vector<WeatherRecord> filteredRecords;
    filterRecordsByMonth(month, year, filteredRecords);

    if (filteredRecords.size() == 0) {
        return false; // No records for the specified month and year
    }

    Vector<float> windSpeeds;
    for (int i = 0; i < filteredRecords.size(); i++){
        float speedKmh = convertMpsToKmh(filteredRecords[i].getWindSpeed());
        windSpeeds.push_back(speedKmh);
    }

    meanSpeed = statistics::calculateMean(windSpeeds);
    stdev = statistics::calculateStandardDeviation(windSpeeds, meanSpeed);
    return true;
}

bool analyzeWeather::calculateTemperatureStats(int month, int year, float & meanTemp, float & stdev) {
    Vector<WeatherRecord> filteredRecords;
    filterRecordsByMonth(month, year, filteredRecords);

    if (filteredRecords.size() == 0) {
        return false; // No records for the specified month and year
    }

    // Collect temperatures from filtered records
    Vector<float> temperatures;
    for (int i = 0; i < filteredRecords.size(); i++){
        temperatures.push_back(filteredRecords[i].getTemperature());
    }

    meanTemp = statistics::calculateMean(temperatures);
    stdev = statistics::calculateStandardDeviation(temperatures, meanTemp);
    return true;
}

bool analyzeWeather::calculateSOlarRadiation(int month, int year, float & totalRadiation) {
    Vector<WeatherRecord> filteredRecords;
    filterRecordsByMonth(month, year, filteredRecords);

    if (filteredRecords.size() == 0) {
        return false; // No records for the specified month and year
    }

    // Calculate total solar radiation in kWh/m2
    totalRadiation = 0.0f;
    for (int i = 0; i < filteredRecords.size(); i++){
        float radiationKwh = convertWm2ToKwhM2(filteredRecords[i].getSolarRadiation());
        totalRadiation += radiationKwh;
    }

    return true;
    
}

void analyzeWeather::getAvailableYears(Vector<int> & years){
    Vector <int> foundYears;

    for (int i = 0; i < weatherData.size(); i++){
        int year = weatherData[i].getDate().GetYear();

        bool alreadyExists = false;
        for (int j = 0; j < foundYears.size(); j++){
            if (foundYears[j] == year){
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

bool analyzeWeather::hasDateForMonth(int month, int year) {
    for (int i = 0; i < weatherData.size(); i++) {
        if (weatherData[i].getDate().GetMonth() == month && weatherData[i].getDate().GetYear() == year) {
            return true; // Found at least one record for the specified month and year
        }
    }
    return false; // No records found for the specified month and year
}

void analyzeWeather::filterRecordsByMonth(int month, int year, Vector<WeatherRecord> & filteredRecords) {
    for (int i = 0; i < weatherData.size(); i++) {
        if (weatherData[i].getDate().GetMonth() == month && weatherData[i].getDate().GetYear() == year) {
            filteredRecords.push_back(weatherData[i]);
        }
    }
}

float analyzeWeather::convertMpsToKmh(float mps) {
    return mps * 3.6f; // Convert meters per second to kilometers per hour
}

float analyzeWeather::convertWm2ToKwhM2(float wPerM2) {
    return wPerM2 * (1.0f / 6.0f) / 1000.0f; // Convert watts per square meter to kilowatt-hours per square meter
}