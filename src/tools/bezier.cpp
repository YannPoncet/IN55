#include "bezier.h"

Bezier::Bezier(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance)
{
    this->P0 = QVector3D(0.0f, 0.0f, 0.0f);
    this->P1 = QVector3D(0.0f, 0.0f, height*stemHeightPart);
    this->P2 = QVector3D(0.0f, 0.0f, height);

    this->constructPoints(height, stemHeightPart, curvatureVariance, anglePosVariance);

    // finding the t for the stem's base
    this->computeBaseAngleAndAxis(this->zeroAngle, this->zeroAxis);
}

QVector3D Bezier::getBezierPoint(float t, double height, double stemHeightPart) {
    float xBezier = pow((1 - t), 2) * this->P0.x()  +  2 * t * (1 -t) * this->P1.x()  +  pow(t, 2) * this->P2.x();
    float yBezier = pow((1 - t), 2) * this->P0.y()  +  2 * t * (1 -t) * this->P1.y()  +  pow(t, 2) * this->P2.y();
    float zBezier = pow((1 - t), 2) * this->P0.z()  +  2 * t * (1 -t) * this->P1.z()  +  pow(t, 2) * this->P2.z();
    QVector3D bezierPoint = QVector3D(xBezier, yBezier, zBezier);
    return bezierPoint  ;
}

void Bezier::computeBaseAngleAndAxis(float& zeroAngle, QVector3D& zeroAxis) {
    QQuaternion qZero = this->getRotationQuaternion(0.00001f);
    qZero.getAxisAndAngle(&zeroAxis, &zeroAngle);
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

    //angle = angle - this->zeroAngle;

    //finding the rotation axis
    QVector3D axis = QVector3D::normal(zAxis, bezierAxis);
    //QVector3D axis = bezierAxis - (QVector3D::dotProduct(zAxis, bezierAxis)/zAxis.lengthSquared())*zAxis;

    // creating the resulting rotation quaternion and returning it
    float radianToDegrees = 180/M_PI;
    QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(axis, angle*radianToDegrees);

    return rotationQuat;
}

void Bezier::applyFullBezierTransformationToVertex(MeshVertex& v, float t, float baseHeight) {
    QVector3D rotationPoint = QVector3D(0, 0, -baseHeight);
    v.translate(-rotationPoint);

    QQuaternion rotationQuat = this->getRotationQuaternion(t);
    QQuaternion straightenQuat = QQuaternion::fromAxisAndAngle(this->zeroAxis, -this->zeroAngle);

    v.rotate(rotationQuat);
    v.rotate(straightenQuat);

    // We can translate the morel back into initial position if needed => comment/uncomment.
    //v.translate(rotationPoint);
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
