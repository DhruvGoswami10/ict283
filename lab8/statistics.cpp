#include "statistics.h"
#include <cmath>

namespace statistics{
    float calculateMean(const Vector<float> & data){
        if (data.size() == 0){
            return 0.0f;
        }

        float sum = 0.0f;
        for (int i = 0; i < data.size(); i++){
            sum += data[i];
        }

        return sum / data.size();
    }

    float calculateStandardDeviation(const Vector<float> & data, float mean){
        if (data.size() <= 1){
            return 0.0f;
        }

        float sumSquareDiff = 0.0f;
        for (int i = 0; i < data.size(); i++){
            float diff = data[i] - mean;
            sumSquareDiff += diff * diff;
        }

        return std::sqrt(sumSquareDiff / (data.size() - 1));
    }

    float calculateStandardDeviation(const Vector<float> & data){
        float mean = calculateMean(data);
        return calculateStandardDeviation(data, mean);
    }

    float calculateSum(const Vector<float> & data){
        float sum = 0.0f;
        for (int i = 0; i < data.size(); i++){
            sum += data[i];
        }
        return sum;
    }
}