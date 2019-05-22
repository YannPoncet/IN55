#ifndef BEZIER_H
#define BEZIER_H

#include <QtMath>
#include <QQuaternion>
#include "normaldistribution.h"

class Bezier
{
public:
    Bezier(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance);
    QQuaternion getRotationQuaternion(float t);
private:
    QVector3D P0;
    QVector3D P1;
    QVector3D P2;

    void constructPoints(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance);
};

#endif // BEZIER_H
