#include "bezier.h"

/*
* Constructor, creates the 3 bezier points and gets the angle and axis of rotation at the base
* @param height is the height of the morel
* @param stemHeightPart is the part of the stem in the total height
* @param curvatureVariance is the curvature variance that we should apply to the curve
* @param anglePosVariance is the angle position variance that we should apply to the second point of the curve
*/
Bezier::Bezier(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance)
{
    // We put default values in the points
    this->P0 = QVector3D(0.0f, 0.0f, 0.0f);
    this->P1 = QVector3D(0.0f, 0.0f, height*stemHeightPart);
    this->P2 = QVector3D(0.0f, 0.0f, height);

    // Move the points according to normal laws
    this->constructPoints(height, stemHeightPart, curvatureVariance, anglePosVariance);

    // Finds the axis and angle at the base of the morel
    this->computeBaseAngleAndAxis(this->zeroAngle, this->zeroAxis);
}


/*
* Returns the point of the Bezier curve at t
* @param t varies from 0 to one
* @return the point at t, going from P0 to P2 and following the curve
*/
QVector3D Bezier::getBezierPoint(float t) {
    float xBezier = pow((1 - t), 2) * this->P0.x()  +  2 * t * (1 -t) * this->P1.x()  +  pow(t, 2) * this->P2.x();
    float yBezier = pow((1 - t), 2) * this->P0.y()  +  2 * t * (1 -t) * this->P1.y()  +  pow(t, 2) * this->P2.y();
    float zBezier = pow((1 - t), 2) * this->P0.z()  +  2 * t * (1 -t) * this->P1.z()  +  pow(t, 2) * this->P2.z();
    QVector3D bezierPoint = QVector3D(xBezier, yBezier, zBezier);
    return bezierPoint;
}


/*
* Returns the axis and angle of rotation at the base of the morel, used to straighten the morel back
* @param zeroAngle will be filled with the angle at base
* @param zeroAngle will be filled with the axis at base
*/
void Bezier::computeBaseAngleAndAxis(float& zeroAngle, QVector3D& zeroAxis) {
    QQuaternion qZero = this->getRotationQuaternion(0.00001f);
    qZero.getAxisAndAngle(&zeroAxis, &zeroAngle);
}


/*
* Returns the rotation quaternion associated with the Bezier point at t
* @param t varies from 0 to 1
* @return the rotation quaternion at t
*/
QQuaternion Bezier::getRotationQuaternion(float t) {
    // We find the B(t), Bezier point at t
    float xBezier = pow((1 - t), 2) * this->P0.x()  +  2 * t * (1 -t) * this->P1.x()  +  pow(t, 2) * this->P2.x();
    float yBezier = pow((1 - t), 2) * this->P0.y()  +  2 * t * (1 -t) * this->P1.y()  +  pow(t, 2) * this->P2.y();
    float zBezier = pow((1 - t), 2) * this->P0.z()  +  2 * t * (1 -t) * this->P1.z()  +  pow(t, 2) * this->P2.z();

    // We find the rotation angle
    QVector3D zAxis = QVector3D(0.0f, 0.0f, 1.0f);
    QVector3D bezierAxis = QVector3D(xBezier, yBezier, zBezier);
    float angle = qAcos(QVector3D::dotProduct(zAxis, bezierAxis)/(zAxis.length()*bezierAxis.length()));

    // We find the rotation axis
    QVector3D axis = QVector3D::normal(zAxis, bezierAxis);

    // We create the resulting rotation quaternion and finally we return it
    float radianToDegrees = 180/M_PI;
    QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(axis, angle*radianToDegrees);

    return rotationQuat;
}


/*
* Apply the bezier transformation to the given vertex
* @param v vertex to apply bezier to
* @param t vertex to apply bezier to
* @param baseHeight is used to compute the real height of the point, if the morel was not centered in 0
*/
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


/*
* This function is used to construct the control points of the Bezier curve
* @param height is the height of the morel
* @param stemHeightPart is the part of the stem in the total height
* @param curvatureVariance is the curvature variance that we should apply to the curve
* @param anglePosVariance is the angle position variance that we should apply to the second point of the curve
*/
void Bezier::constructPoints(double height, double stemHeightPart, double curvatureVariance, double anglePosVariance) {
    float xValue = randomGenerator.getNormalNumber<float>(0, curvatureVariance);
    float yValue = randomGenerator.getNormalNumber<float>(0, curvatureVariance);
    float zValue = randomGenerator.getNormalNumber<float>(height*stemHeightPart*0.5, anglePosVariance);
    if(zValue <= 0) zValue = -zValue;

    this->P1 = QVector3D(xValue, yValue, zValue);

    xValue = randomGenerator.getNormalNumber<float>(0, curvatureVariance);
    yValue = randomGenerator.getNormalNumber<float>(0, curvatureVariance);
    zValue = randomGenerator.getNormalNumber<float>(height, anglePosVariance);
    if(zValue <= 0) zValue = -zValue;

    this->P2 = QVector3D(xValue, yValue, zValue);
}
