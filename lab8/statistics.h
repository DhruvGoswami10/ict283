#ifndef STATISTICS_H
#define STATISTICS_H

#include "vector.h"

/**
 * @file statistics.h
 * @brief Data loading and CSV parsing functionality
 * @author Dhruv Goswami
 * @date 20/06/2025
 */

/**
 * @namespace statistics
 * @brief Contains statistical calculation functions
 */
namespace statistics{
    /**
     * @brief Calculates the arithmetic mean of a dataset
     * @param data Vector containing float values
     * @return Mean value, or 0.0 if data is empty
     */
    float calculateMean(const Vector<float> & data);

    /**
     * @brief Calculates standard deviation with known mean
     * @param data Vector containing float values
     * @param mean Pre-calculated mean of the dataset
     * @return Sample standard deviation using (n-1) denominator
     */
    float calculateStandardDeviation(const Vector<float> & data, float mean);

    /**
     * @brief Calculates standard deviation (calculates mean internally)
     * @param data Vector containing float values
     * @return Sample standard deviation
     */
    float calculateStandardDeviation(const Vector<float> & data);

    /**
     * @brief Calculates the sum of all values in a dataset
     * @param data Vector containing float values
     * @return Sum of all values
     */
    float calculateSum(const Vector<float> & data);
}

#endif
