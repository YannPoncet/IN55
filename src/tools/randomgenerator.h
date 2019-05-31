#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <stdlib.h>
#include <random>
#include <QDebug>
#include <ctime>    // For time()
#include <QtMath>

class RandomGenerator
{
public:
    RandomGenerator() {
        //std::random_device rd;  //Will be used to obtain a seed for the random number engine
        srand(time(nullptr));

        this->generator = std::default_random_engine(rand());
        this->getRand(0,1000); //Without that it's not truly random, don't know why exactly
        this->seed = this->getRand(0,1000000);

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

    uint32_t xor128_fastRandom() {
        static uint32_t x = this->seed;
        static uint32_t y = 362436069;
        static uint32_t z = 521288629;
        static uint32_t w = 88675123;
        uint32_t t;
        t = x ^ (x << 11);
        x = y; y = z; z = w;
        return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
    }

    int getFastRandom(int min, int max) {
        return qAbs(this->xor128_fastRandom() % (max - min + 1)) + min;
    }

    std::default_random_engine getGenerator() {
        return generator;
    }

private:
    std::default_random_engine generator;
    int seed;
};

#endif // RANDOMGENERATOR_H
