#ifndef VORONOI_H
#define VORONOI_H

#include <QtMath>
#include <QVector>
#include <QVector2D>

class Voronoi
{
public:
    Voronoi(int xMax, int yMax, int maxNbPoints, int width, double fMax, double fMin);
    double getFactorAt(double x, double y);

private:
    int xMax;
    int yMax;
    int maxNbPoints;
    int width;
    float fMax;
    float fMin;

    int distanceType;
    double separationFactor;
    QVector<QVector2D> points;


    double dist(int x, int y);
    void generatePoints();
    int randgen(int max);
    double factorFunction(double x);
};

#endif // VORONOI_H
