/**
 * @file statistics.cpp
 * @brief Implementation of statistical calculation functions
 * @author Dhruv Goswami
 * @date 20/06/2025
 */

#include "statistics.h"
#include <cmath>

namespace statistics {

    float calculateMean(const Vector<float>& data) {
        if (data.size() == 0) {
            return 0.0f;
        }

        float sum = 0.0f;
        for (int i = 0; i < data.size(); i++) {
            sum += data[i];
        }

        return sum / data.size();
    }

    float calculateStandardDeviation(const Vector<float>& data, float mean) {
        if (data.size() <= 1) {
            return 0.0f;
        }

        float sumSquareDiff = 0.0f;
        for (int i = 0; i < data.size(); i++) {
            float diff = data[i] - mean;
            sumSquareDiff += diff * diff;
        }

        return std::sqrt(sumSquareDiff / (data.size() - 1));
    }

    float calculateStandardDeviation(const Vector<float>& data) {
        float mean = calculateMean(data);
        return calculateStandardDeviation(data, mean);
    }

    float calculateSum(const Vector<float>& data) {
        float sum = 0.0f;
        for (int i = 0; i < data.size(); i++) {
            sum += data[i];
        }
        return sum;
    }

    float calculatesPCC(const Vector<float>& dataX, const Vector<float>& dataY) {
        // Check if datasets have same size and are not empty
        if (dataX.size() != dataY.size() || dataX.size() == 0) {
            return 0.0f;
        }

        int n = dataX.size();
        if (n < 2) {
            return 0.0f; // Need at least 2 points for correlation
        }

        // Calculate means
        float meanX = calculateMean(dataX);
        float meanY = calculateMean(dataY);

        // Calculate numerator
        float numerator = 0.0f;
        float sumSquareX = 0.0f;
        float sumSquareY = 0.0f;

        for (int i = 0; i < n; i++) {
            float diffX = dataX[i] - meanX;
            float diffY = dataY[i] - meanY;

            numerator += diffX * diffY;
            sumSquareX += diffX * diffX;
            sumSquareY += diffY * diffY;
        }

        // Calculate denominator
        float denominator = std::sqrt(sumSquareX * sumSquareY);

        // Avoid division by zero
        if (denominator == 0.0f) {
            return 0.0f;
        }

        return numerator / denominator;
    }

    float calculateMAD(const Vector<float>& data) {
        if (data.size() == 0) {
            return 0.0f;
        }

        float mean = calculateMean(data);
        return calculateMAD(data, mean);
    }

    float calculateMAD(const Vector<float>& data, float mean) {
        if (data.size() == 0) {
            return 0.0f;
        }

        float sumAbsoluteDiff = 0.0f;
        for (int i = 0; i < data.size(); i++) {
            sumAbsoluteDiff += std::abs(data[i] - mean);
        }

        return sumAbsoluteDiff / data.size();
    }

} // namespace statistics
