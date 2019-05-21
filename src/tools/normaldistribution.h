#ifndef NORMALDISTRIBUTION_H
#define NORMALDISTRIBUTION_H

#include <stdlib.h>
#include <random>
#include <QDebug>

class NormalDistribution
{
public:
    template <class T>
    static T getNormalNumber(T expectation, T variance);
};

#endif // NORMALDISTRIBUTION_H
