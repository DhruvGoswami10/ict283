#include "loadWeatherData.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>

loadWeatherData::loadWeatherData(){}

// Load data from all files listed in data_source.txt
bool loadWeatherData::loadAllDataFiles(Vector<WeatherRecord> & records) {
    Vector<std::string> filenames;

    if (!getAllDataSourceFilenames(filenames)) {
        return false;
    }

    std::cout << "Found" << filenames.size() << " data files to load: " << std::endl;

    for (int i = 0; i < filenames.size(); i++){
        std::cout << "Loading: " << filenames[i] << std::endl;

        Vector<WeatherRecord> fileRecords;
        if(loadData(filenames[i], fileRecords)) {
            for (int j = 0; i < fileRecords.size(); j++) {
                records.push_back(fileRecords[j]);
            }
            std::cout << " Loaded " << fileRecords.size() << " records" << std::endl;
        }
        else {
            std::cerr << " Failed to load " << filenames[i] << std::endl;
        }
    }
    return records.size() > 0;
}

// Get all filenames form data_source.txt
bool loadWeatherData::getAllDataSourceFilenames(Vector<std::string> & filenames) {
    std::ifstream sourceFile("data/data_source.txt");
    if (!sourceFile) {
        std::cerr << "Cannot open data_source.txt" << std::endl;
        return false;
    }

    std::string filename;
    while (std::getline(sourceFile, filename)) {
        if (!filename.empty()) {
            filenames.push_back("data/" + filename);
        }
    }

    sourceFile.close();

    if (filenames.size() == 0) {
        std::cerr << "No filenames found in data_source.txt" << std::endl;
        return false;
    }

    return true;
}

std::string loadWeatherData::getDataSourceFilename(){
    std::ifstream sourceFile("data/data_source.txt");
    if (!sourceFile){
        std::cerr << "cannot open data_source.txt" << std::endl;
        return "";
    }

    std::string filename;
    std::getline(sourceFile, filename);
    sourceFile.close();

    return "data/" + filename;
}

bool loadWeatherData::loadData(const std::string & filename, Vector<WeatherRecord> & records){
    std::ifstream file(filename);
    if(!file) {
        std::cerr << "Cannot open the file " << filename << std::endl;
        return false;
    }

    //read the header to find the column indexes
    std::string headerLine;
    if (!std::getline(file, headerLine)) {
        std::cerr << "Cannot read the header line from the file" << std::endl;
        return false;
    }

    Vector<std::string> headers;
    parseCSVLine(headerLine, headers);

    // Find the indexes of the required columns
    int wastIndex = findColumnIndex(headers, "WAST");
    int sIndex = findColumnIndex(headers, "S");
    int tIndex = findColumnIndex(headers, "T");
    int srIndex = findColumnIndex(headers, "SR");

    if (wastIndex == -1 || sIndex == -1 || tIndex == -1 || srIndex == -1) {
        std::cerr << "Cannot find required columns in the header file" << std::endl;
        return false;
    }

    int maxIndex = wastIndex;
    if (sIndex > maxIndex) maxIndex = sIndex;
    if (tIndex > maxIndex) maxIndex = tIndex;
    if (srIndex > maxIndex) maxIndex = srIndex;

    //read the data lines
    std::string line;
    while (std::getline(file, line)){
        Vector<std::string> fields;
        parseCSVLine(line, fields);

        if (fields.size() <= maxIndex){
            continue;
        } // skip lines with incomplete data

        //skip lines with missing data
        if (isMissingData(fields[sIndex]) ||
            isMissingData(fields[tIndex]) ||
            isMissingData(fields[srIndex])) {
            continue;
        }

        //parse date and time from WAST field
        std::string datetime = fields[wastIndex];
        std::stringstream dtStream(datetime);
        std::string dateStr, timeStr;
        dtStream >> dateStr >> timeStr;

        Date date(dateStr);
        Time time(timeStr);

        // parse numeric values
        float windSpeed = stringToFloat(fields[sIndex]);
        float temperature = stringToFloat(fields[tIndex]);
        float solarRadiation = stringToFloat(fields[srIndex]);

        // filter solar radiation only >= 100 W/m2
        if (solarRadiation >= 100.0f){
            WeatherRecord record(date, time, windSpeed, temperature, solarRadiation);
            records.push_back(record);
        }
    }

    file.close();
    return true;
}

int loadWeatherData::findColumnIndex(const Vector<std::string> & headers, const std::string & targetHeader) {
    for (int i = 0; i < headers.size(); ++i) {
        if (headers[i] == targetHeader) {
            return i;
        }
    }
    return -1; // Not found
}

void loadWeatherData::parseCSVLine(const std::string & line, Vector<std::string> & fields) {
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }
}

bool loadWeatherData::isMissingData(const std::string & value) {
    return value.empty() || value == "NA" || value == "N/A";
}

float loadWeatherData::stringToFloat(const std::string & str) {
    if (str.empty()) {
        return 0.0f;
    }
    return static_cast<float>(atof(str.c_str()));
}
