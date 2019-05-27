#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <stdlib.h>
#include <random>
#include <QDebug>
#include <ctime>    // For time()

class RandomGenerator
{
public:
    RandomGenerator() {
        //std::random_device rd;  //Will be used to obtain a seed for the random number engine
        this->generator = std::default_random_engine(time(0));
        //this->generator.seed(122222222);
    }

    // Templated function that returns a number following a normal distribution function
    template <typename T>
    T getNormalNumber(T expectation, T variance) {
        std::normal_distribution<T> distribution(expectation, sqrt(variance));
        return distribution(this->generator);
    }

    int getRand(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(this->generator);
    }

    std::default_random_engine getGenerator() {
        return generator;
    }

private:
    std::default_random_engine generator;
};

#endif // RANDOMGENERATOR_H
