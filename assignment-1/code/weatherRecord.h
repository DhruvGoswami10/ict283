#ifndef WEATHER_RECORD_H
#define WEATHER_RECORD_H

#include "date.h"
#include "time.h"

/**
 * @file weatherRecord.h
 * @brief WeatherRecord class for storing individual weather measurements
 * @author Dhruv Goswami
 * @date 20/06/2025
 */


/**
 * @class WeatherRecord
 * @brief Encapsulates a single weather data record with date, time, and measurements
 */
class WeatherRecord{
public:
    /**
     * @brief Default constructor
     */
    WeatherRecord();

    /**
     * @brief Parameterized constructor
     * @param d Date of measurement
     * @param t Time of measurement
     * @param windSpeed Wind speed in m/s
     * @param temp Temperature in degrees Celsius
     * @param solarRadiation Solar radiation in W/m²
     */
    WeatherRecord(const Date & d, const Time & t, float windSpeed, float temp, float solarRadiation);

    /**
     * @brief Gets the date of measurement
     * @return Date object representing when measurement was taken
     */
    Date getDate() const;

    /**
     * @brief Gets the time of measurement
     * @return Time object representing when measurement was taken
     */
    Time getTime() const;

    /**
     * @brief Gets the wind speed measurement
     * @return Wind speed in meters per second
     */
    float getWindSpeed() const;

    /**
     * @brief Gets the temperature measurement
     * @return Temperature in degrees Celsius
     */
    float getTemperature() const;

    /**
     * @brief Gets the solar radiation measurement
     * @return Solar radiation in watts per square meter
     */
    float getSolarRadiation() const;

    /**
     * @brief Sets the date of measurement
     * @param d Date to set
     */
    void setDate(const Date & d);

    /**
     * @brief Sets the time of measurement
     * @param t Time to set
     */
    void setTime(const Time & t);

    /**
     * @brief Sets the wind speed measurement
     * @param speed Wind speed in m/s
     */
    void SetWindSpeed(float speed);

    /**
     * @brief Sets the temperature measurement
     * @param temp Temperature in degrees Celsius
     */
    void setTemperature(float temp);

    /**
     * @brief Sets the solar radiation measurement
     * @param radiation Solar radiation in W/m²
     */
    void setSolarRadiation(float radiation);

private:
    Date date;              // Date of measurement
    Time time;              // Time of measurement
    float windSpeed;        // Wind speedin m/s
    float temperature;      // Temp in degrees celsius
    float solarRadiation;   // Solar radiation in W/m2
};

#endif
