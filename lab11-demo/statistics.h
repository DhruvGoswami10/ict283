#ifndef STATISTICS_H
#define STATISTICS_H

#include "vector.h"

/**
 * @file statistics.h
 * @brief Statistical calculation functions - NOT coupled to weather data types
 * @author Dhruv Goswami
 * @date 20/06/2025
 *
 * All functions work with generic Vector<float> to ensure NO coupling to weather data types
 * This allows reuse with any numeric data, not just weather measurements
 */

/**
 * @namespace statistics
 * @brief Contains statistical calculation functions
 */
namespace statistics {
    /**
     * @brief Calculates the arithmetic mean of a dataset
     * @param data Vector containing float values
     * @return Mean value, or 0.0 if data is empty
     */
    float calculateMean(const Vector<float>& data);

    /**
     * @brief Calculates standard deviation with known mean
     * @param data Vector containing float values
     * @param mean Pre-calculated mean of the dataset
     * @return Sample standard deviation using (n-1) denominator
     */
    float calculateStandardDeviation(const Vector<float>& data, float mean);

    /**
     * @brief Calculates standard deviation (calculates mean internally)
     * @param data Vector containing float values
     * @return Sample standard deviation
     */
    float calculateStandardDeviation(const Vector<float>& data);

    /**
     * @brief Calculates the sum of all values in a dataset
     * @param data Vector containing float values
     * @return Sum of all values
     */
    float calculateSum(const Vector<float>& data);

    /**
     * @brief Calculates Sample Pearson Correlation Coefficient (sPCC)
     * @param dataX First dataset (X values)
     * @param dataY Second dataset (Y values)
     * @return Correlation coefficient between -1 and 1, or 0.0 if calculation impossible
     */
    float calculatesPCC(const Vector<float>& dataX, const Vector<float>& dataY);

    /**
     * @brief Calculates Mean Absolute Deviation (MAD)
     * @param data Vector containing float values
     * @return Mean absolute deviation from the mean
     */
    float calculateMAD(const Vector<float>& data);

    /**
     * @brief Calculates Mean Absolute Deviation with known mean
     * @param data Vector containing float values
     * @param mean Pre-calculated mean of the dataset
     * @return Mean absolute deviation from the given mean
     */
    float calculateMAD(const Vector<float>& data, float mean);
}

#endif // STATISTICS_H
