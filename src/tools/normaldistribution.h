#ifndef NORMALDISTRIBUTION_H
#define NORMALDISTRIBUTION_H

#include <stdlib.h>
#include <random>
#include <QDebug>

class NormalDistribution
{
public:
    // Templated function that returns a number following a normal distribution function
    template <typename T>
    static T getNormalNumber(T expectation, T variance) {
        std::default_random_engine generator;
        std::normal_distribution<T> distribution(expectation, sqrt(variance));
        return distribution(generator);
    }
};

#endif // NORMALDISTRIBUTION_H
