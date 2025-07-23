#ifndef TIME_H
#define TIME_H

#include <string>

/**
* @file time.h
* @brief Time class for handling time operations in 24-hour format
* @author Dhruv Goswami
* @date 20/06/2025
*/

/**
 * @class Time
 * @brief Represents time in 24-hour format with hours, minutes, and seconds
 */
class Time {
public:
     /**
     * @brief Default constructor
     */
    Time();

     /**
     * @brief Constructor to initialize from time string
     * @param timeStr Time string in format "HH:MM:SS"
     */
    Time(const std::string & timeStr);

    /**
     * @brief Gets the hour component
     * @return Hour value (0-23)
     */
    int getHour() const;

    /**
     * @brief Gets the minute component
     * @return Minute value (0-59)
     */
    int getMin() const;

     /**
     * @brief Gets the second component
     * @return Second value (0-59)
     */
    int getSec() const;

    /**
     * @brief Sets all time components
     * @param h Hour value
     * @param m Minute value
     * @param s Second value
     */
    void setTime(int h, int m, int s);

    /**
     * @brief Converts time to string representation
     * @return String in format "HH:MM:SS" with zero-padding
     */
    std::string toString() const; //what does this do?
    // Converts the time to a string in the format "HH:MM:SS"

private:
    int hour;   //Hour Component
    int min;    //Minute component
    int sec;    //Second component
};

#endif
