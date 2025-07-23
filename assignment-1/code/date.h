#ifndef DATE_H
#define DATE_H

#include <string>

/**
 * @file date.h
 * @brief Date class for handling date operations
 * @author Dhruv Goswami
 * @date 20/06/2025
 */

/**
 * @class Date
 * @brief Represents a date with day, month, and year.
 */
class Date {
public:
    /**
     * @brief Default constructor.
     */
    Date();

    /**
     * @brief Constructor to initialize with specific day, month, and year.
     * @param day Day value.
     * @param month Month value.
     * @param year Year value.
     */
    Date(int day, int month, int year);

    /**
     * @brief Constructor to initialize date from a string (format: DD/MM/YYYY).
     * @param dateStr Date string.
     */
    Date(const std::string & dateStr);

    /**
     * @brief Gets the day.
     * @return Day value.
     */
    int GetDay() const;

    /**
     * @brief Gets the month.
     * @return Month value.
     */
    int GetMonth() const;

    /**
     * @brief Gets the year.
     * @return Year value.
     */
    int GetYear() const;

    /**
     * @brief Sets the date.
     * @param day Day value.
     * @param month Month value.
     * @param year Year value.
     */
    void SetDate(int day, int month, int year);

private:
    int day;    ///< Day component of the date
    int month;  ///< Month component of the date
    int year;   ///< Year component of the date
};

#endif // DATE_H
