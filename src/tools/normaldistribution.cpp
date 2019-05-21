#include "normaldistribution.h"

template <class T>
T NormalDistribution::getNormalNumber(T expectation, T variance) {
    std::default_random_engine generator;
    std::normal_distribution<T> distribution(expectation, sqrt(variance));
    return distribution(generator);
}
