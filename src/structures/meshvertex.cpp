#include "meshvertex.h"

MeshVertex::MeshVertex()
{
    this->right = nullptr;
    this->left = nullptr;
    this->top = nullptr;
    this->bottom = nullptr;
}


/*
* Computes the normal vector of the vertex. Stores it in this->normal.
*/
void MeshVertex::computeNormalVector() {
    // Doing the normals clockwise so they "go out"
    QVector3D topRightNormal;
    QVector3D topLeftNormal;
    QVector3D bottomLeftNormal;
    QVector3D bottomRightNormal;

    if(this->right!=nullptr && this->top!=nullptr) {
        topRightNormal = QVector3D::crossProduct((this->position-this->right->position), (this->position-this->top->position));
    }

    if(this->top!=nullptr && this->left!=nullptr) {
        topLeftNormal = QVector3D::crossProduct((this->position-this->top->position), (this->position-this->left->position));
    }

    if(this->left!=nullptr && this->bottom!=nullptr) {
        bottomLeftNormal = QVector3D::crossProduct((this->position-this->left->position), (this->position-this->bottom->position));
    }

    if(this->bottom!=nullptr && this->right!=nullptr) {
        bottomRightNormal = QVector3D::crossProduct((this->position-this->bottom->position), (this->position-this->right->position));
    }

    // The normal is weighted as the normals length is equal to the area of their faces
    this->normal = topRightNormal + topLeftNormal + bottomLeftNormal + bottomRightNormal;
}


/*
* @return x position of the vetex.
*/
float MeshVertex::x() {
    return this->position.x();
}


/*
* @return y position of the vetex.
*/
float MeshVertex::y() {
    return this->position.y();
}


/*
* @return z position of the vetex.
*/
float MeshVertex::z() {
    return this->position.z();
}


/*
* Sets x position of the vertex, and updates its normal vector.
*/
void MeshVertex::setX(float x) {
    this->position.setX(x);
    this->computeNormalVector();
}


/*
* Sets y position of the vertex, and updates its normal vector.
*/
void MeshVertex::setY(float y) {
    this->position.setY(y);
    this->computeNormalVector();
}


/*
* Sets z position of the vertex, and updates its normal vector.
*/
void MeshVertex::setZ(float z) {
    this->position.setZ(z);
    this->computeNormalVector();
}


/*
* Sets x;y;z positions of the vertex, and updates its normal vector.
*/
void MeshVertex::setPosition(float x, float y, float z) {
    this->position.setX(x);
    this->position.setY(y);
    this->position.setZ(z);
    this->computeNormalVector();
}


/*
* Rescale the vertex according to the origin 0;0;0
* @param scale represents the scale on x, on y and on z that we should apply
*/
void MeshVertex::rescale(QVector3D scale) {
    QMatrix4x4 rescaleMatrix = QMatrix4x4(  scale.x(),   0,           0,           0,
                                            0,           scale.y(),   0,           0,
                                            0,           0,           scale.z(),   0,
                                            0,           0,           0,           1);
    this->position = rescaleMatrix*this->position;
}


/*
* Rescale the vertex according to the origin 0;0;0
* @param scale represents the scale that we should apply on x, y and z
*/
void MeshVertex::rescale(float scale) {
    QMatrix4x4 rescaleMatrix = QMatrix4x4(  scale,   0,       0,       0,
                                            0,       scale,   0,       0,
                                            0,       0,       scale,   0,
                                            0,       0,       0,       1);
    this->position = rescaleMatrix*this->position;
}


/*
* Translates the vertex following an axis
* @param axis is the axis of translation
*/
void MeshVertex::translate(QVector3D axis) {
    this->position += axis;
}


/*
* Apply a quaternion rotation to the vertex
* @param rotationQuat is the rotation quaternion to apply
*/
void MeshVertex::rotate(QQuaternion rotationQuat) {
    this->position = rotationQuat*this->position;
}


/*
* Apply a quaternion rotation to the vertex, the axis of the quaternion goes through a specific point
* @param rotationQuat is the rotation quaternion to apply
* @param point is the point through which the axis goes
*/
void MeshVertex::rotate(QQuaternion rotationQuat, QVector3D point) {
    this->position -= point;
    this->position = rotationQuat*this->position;
    this->position += point;
}


/*
* Apply a rotation with an angle and an axis
* @param angle is the angle of rotation
* @param axis is the axis of rotation
*/
void MeshVertex::rotate(float angle, QVector3D axis) {
    float radianToDegrees = 180/M_PI;
    QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(axis, angle*radianToDegrees);

    this->position = rotationQuat*this->position;
}


/*
* Apply a rotation with an angle and an axis going through a point
* @param angle is the angle of rotation
* @param axis is the axis of rotation
* @param point is the point through which the axis goes
*/
void MeshVertex::rotate(float angle, QVector3D axis, QVector3D point) {
    float radianToDegrees = 180/M_PI;
    QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(axis, angle*radianToDegrees);

    this->position -= point;
    this->position = rotationQuat*this->position;
    this->position += point;
}
