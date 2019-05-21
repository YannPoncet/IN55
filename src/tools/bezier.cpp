#include "bezier.h"

Bezier::Bezier(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance)
{
    this->P0 = QVector3D(0.0f, 0.0f, 0.0f);
    this->P1 = QVector3D(0.0f, 0.0f, height*stemHeightPart/100);
    this->P2 = QVector3D(0.0f, 0.0f, height);

    this->constructPoints(height, stemHeightPart, curvatureVariance, anglePosVariance);
}

QQuaternion Bezier::getRotationQuaternion(double horizontalDivisionHeight, double height) {
    // Finding the B(t), Bezier point at t
    double t = horizontalDivisionHeight/height;
    double xBezier = pow((1 - t), 2) * this->P0.x()  +  2 * t * (1 -t) * this->P1.x()  +  pow(t, 2) * this->P2.x();
    double yBezier = pow((1 - t), 2) * this->P0.y()  +  2 * t * (1 -t) * this->P1.y()  +  pow(t, 2) * this->P2.y();
    double zBezier = pow((1 - t), 2) * this->P0.z()  +  2 * t * (1 -t) * this->P1.z()  +  pow(t, 2) * this->P2.z();

    // finding the rotation angle
    QVector3D zAxis = QVector3D(0.0f, 0.0f, 1.0f);
    QVector3D bezierAxis = QVector3D(xBezier, yBezier, zBezier);
    float angle = qAcos(QVector3D::dotProduct(zAxis, bezierAxis)/(zAxis.length()*bezierAxis.length()));

    //finding the rotation axis
    QVector3D axis = bezierAxis - (QVector3D::dotProduct(zAxis, bezierAxis)/zAxis.lengthSquared())*zAxis;

    // creating the resulting rotation quaternion and returning it
    float radianToDegrees = 180/M_PI;
    QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(axis, angle*radianToDegrees);

    return rotationQuat;
}

void Bezier::constructPoints(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance) {
    float xValue = NormalDistribution::getNormalNumber<float>(0, curvatureVariance);
    float yValue = NormalDistribution::getNormalNumber<float>(0, curvatureVariance);
    float zValue = NormalDistribution::getNormalNumber<float>(height*stemHeightPart/100, anglePosVariance);

    this->P1 = QVector3D(xValue, yValue, zValue);

    xValue = NormalDistribution::getNormalNumber<float>(0, curvatureVariance);
    yValue = NormalDistribution::getNormalNumber<float>(0, curvatureVariance);
    zValue = NormalDistribution::getNormalNumber<float>(height, anglePosVariance);

    this->P2 = QVector3D(xValue, yValue, zValue);
}
