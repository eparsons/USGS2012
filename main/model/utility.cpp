#include "utility.h"

void Utility::boundLower(float & value, float lowerBound) {
    if(value < lowerBound) {
        value = lowerBound;
    }
}

void Utility::boundUpper(float & value, float upperBound) {
    if (value > upperBound) {
        value = upperBound;
    }
}

void Utility::boundValue(float & value, float lowerBound, float upperBound) {
    if(value < lowerBound) {
        value = lowerBound;
    } else if (value > upperBound) {
        value = upperBound;
    }
}

void Utility::boundPercentage(float & value) {
    boundValue(value, 0.0, 1.0);
}
