#ifndef BEZIER_H
#define BEZIER_H

#include <QOpenGLFunctions>
#include <QtMath>
#include <QQuaternion>

#include "../structures/meshvertex.h"
#include "../globals.h"

class Bezier
{
public:
    Bezier(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance);
    QQuaternion getRotationQuaternion(float t);
    QVector3D getBezierPoint(float t);
    void applyFullBezierTransformationToVertex(MeshVertex& v, float t, float baseHeight);
    float getZeroAngle();

private:
    QVector3D P0;
    QVector3D P1;
    QVector3D P2;

    float zeroAngle;
    QVector3D zeroAxis;

    void constructPoints(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance);
    void computeBaseAngleAndAxis(float& zeroAngle, QVector3D& zeroAxis);
};

#endif // BEZIER_H
