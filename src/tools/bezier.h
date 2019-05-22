#ifndef BEZIER_H
#define BEZIER_H

#include <QOpenGLFunctions>
#include <QtMath>
#include <QQuaternion>
#include "normaldistribution.h"

class Bezier
{
public:
    Bezier(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance, GLushort stemNumberOfHorizontalDivisions);
    QQuaternion getRotationQuaternion(float t);
private:
    QVector3D P0;
    QVector3D P1;
    QVector3D P2;
    float zeroAngle;
    NormalDistribution normalDistribution;

    void constructPoints(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance);
    float getRotationAngleStemBase(float t);
};

#endif // BEZIER_H
