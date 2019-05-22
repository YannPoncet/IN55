#include "bezier.h"

Bezier::Bezier(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance, GLushort stemNumberOfHorizontalDivisions)
{
    this->P0 = QVector3D(0.0f, 0.0f, 0.0f);
    this->P1 = QVector3D(0.0f, 0.0f, height*stemHeightPart);
    this->P2 = QVector3D(0.0f, 0.0f, height);

    this->constructPoints(height, stemHeightPart, curvatureVariance, anglePosVariance);

    // finding the t for the stem's base
    double p = height*stemHeightPart/stemNumberOfHorizontalDivisions;
    float t = ((stemHeightPart*height)+(-p*(stemNumberOfHorizontalDivisions-1)))/height;
    this->zeroAngle = this->getRotationAngleStemBase(t);
}

QVector3D Bezier::getBezierPoint(float t) {
    float xBezier = pow((1 - t), 2) * this->P0.x()  +  2 * t * (1 -t) * this->P1.x()  +  pow(t, 2) * this->P2.x();
    float yBezier = pow((1 - t), 2) * this->P0.y()  +  2 * t * (1 -t) * this->P1.y()  +  pow(t, 2) * this->P2.y();
    float zBezier = pow((1 - t), 2) * this->P0.z()  +  2 * t * (1 -t) * this->P1.z()  +  pow(t, 2) * this->P2.z();
    QVector3D bezierPoint = QVector3D(xBezier, yBezier, zBezier);
    return bezierPoint  ;
}

float Bezier::getRotationAngleStemBase(float t) {
    // Finding the B(t), Bezier point at t
    float xBezier = pow((1 - t), 2) * this->P0.x()  +  2 * t * (1 -t) * this->P1.x()  +  pow(t, 2) * this->P2.x();
    float yBezier = pow((1 - t), 2) * this->P0.y()  +  2 * t * (1 -t) * this->P1.y()  +  pow(t, 2) * this->P2.y();
    float zBezier = pow((1 - t), 2) * this->P0.z()  +  2 * t * (1 -t) * this->P1.z()  +  pow(t, 2) * this->P2.z();

    // finding the rotation angle
    QVector3D zAxis = QVector3D(0.0f, 0.0f, 1.0f);
    QVector3D bezierAxis = QVector3D(xBezier, yBezier, zBezier);
    float angle = qAcos(QVector3D::dotProduct(zAxis, bezierAxis)/(zAxis.length()*bezierAxis.length()));
    return angle;
}

QQuaternion Bezier::getRotationQuaternion(float t) {
    // Finding the B(t), Bezier point at t
    float xBezier = pow((1 - t), 2) * this->P0.x()  +  2 * t * (1 -t) * this->P1.x()  +  pow(t, 2) * this->P2.x();
    float yBezier = pow((1 - t), 2) * this->P0.y()  +  2 * t * (1 -t) * this->P1.y()  +  pow(t, 2) * this->P2.y();
    float zBezier = pow((1 - t), 2) * this->P0.z()  +  2 * t * (1 -t) * this->P1.z()  +  pow(t, 2) * this->P2.z();

    // finding the rotation angle
    QVector3D zAxis = QVector3D(0.0f, 0.0f, 1.0f);
    QVector3D bezierAxis = QVector3D(xBezier, yBezier, zBezier);
    float angle = qAcos(QVector3D::dotProduct(zAxis, bezierAxis)/(zAxis.length()*bezierAxis.length()));
    // changing the angle so the shroom is standing up
    angle = angle - this->zeroAngle;

    //finding the rotation axis
    QVector3D axis = QVector3D::normal(zAxis, bezierAxis);
    //QVector3D axis = bezierAxis - (QVector3D::dotProduct(zAxis, bezierAxis)/zAxis.lengthSquared())*zAxis;

    // creating the resulting rotation quaternion and returning it
    float radianToDegrees = 180/M_PI;
    QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(axis, angle*radianToDegrees);

    return rotationQuat;
}

void Bezier::constructPoints(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance) {
    float xValue = this->normalDistribution.getNormalNumber<float>(0, curvatureVariance);
    float yValue = this->normalDistribution.getNormalNumber<float>(0, curvatureVariance);
    float zValue = this->normalDistribution.getNormalNumber<float>(height*stemHeightPart, anglePosVariance);

    this->P1 = QVector3D(xValue, yValue, zValue);
    qDebug() << "P1=" << P1;

    xValue = this->normalDistribution.getNormalNumber<float>(0, curvatureVariance);
    yValue = this->normalDistribution.getNormalNumber<float>(0, curvatureVariance);
    zValue = this->normalDistribution.getNormalNumber<float>(height, anglePosVariance);

    this->P2 = QVector3D(xValue, yValue, zValue);
    qDebug() << "P2=" << P2;
}
