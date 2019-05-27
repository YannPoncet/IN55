#ifndef VORONOI_H
#define VORONOI_H

#include <QtMath>
#include <QVector>
#include <QVector2D>
#include <QDebug>

#include "../globals.h"

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

    double dist(double x, double y);
    void generatePoints();
    int randgen(int max);
    double factorFunction(double x);
    QVector2D perpendicularLineLineIntersection(QVector2D A, QVector2D B, QVector2D C, QVector2D D, QVector2D Pab, QVector2D Pcd);
};

#endif // VORONOI_H
