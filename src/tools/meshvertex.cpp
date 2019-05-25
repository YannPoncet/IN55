#include "meshvertex.h"

MeshVertex::MeshVertex()
{
    this->right = nullptr;
    this->left = nullptr;
    this->top = nullptr;
    this->bottom = nullptr;
}

void MeshVertex::computeNormalVector() {
    // doing the normals clockwise so they "go out"
    QVector3D topRightNormal;
    QVector3D topLeftNormal;
    QVector3D bottomLeftNormal;
    QVector3D bottomRightNormal;

    if(this->right!=nullptr && this->top!=nullptr) {
        topRightNormal = QVector3D::crossProduct(this->right->position, this->top->position);
    }

    if(this->top!=nullptr && this->left!=nullptr) {
        topLeftNormal = QVector3D::crossProduct(this->top->position, this->left->position);
    }

    if(this->left!=nullptr && this->bottom!=nullptr) {
        bottomLeftNormal = QVector3D::crossProduct(this->left->position, this->bottom->position);
    }

    if(this->bottom!=nullptr && this->right!=nullptr) {
        bottomRightNormal = QVector3D::crossProduct(this->bottom->position, this->right->position);
    }


    // the normal is weighted as the normals length is equal to the area of their faces
    this->normal = topRightNormal + topLeftNormal + bottomLeftNormal + bottomRightNormal;
    //this->normal.normalize();
}

float MeshVertex::x() {
    return this->position.x();
}

float MeshVertex::y() {
    return this->position.y();
}

float MeshVertex::z() {
    return this->position.z();
}

void MeshVertex::setX(float x) {
    this->position.setX(x);
    this->computeNormalVector();
}

void MeshVertex::setY(float y) {
    this->position.setY(y);
    this->computeNormalVector();
}

void MeshVertex::setZ(float z) {
    this->position.setZ(z);
    this->computeNormalVector();
}

void MeshVertex::setPosition(float x, float y, float z) {
    this->position.setX(x);
    this->position.setY(y);
    this->position.setZ(z);
    this->computeNormalVector();
}

void MeshVertex::rescale(QVector3D scale) {
    QMatrix4x4 rescaleMatrix = QMatrix4x4(  scale.x(),   0,           0,           0,
                                            0,           scale.y(),   0,           0,
                                            0,           0,           scale.z(),   0,
                                            0,           0,           0,           1);
    this->position = rescaleMatrix*this->position;
}

void MeshVertex::rescale(float scale) {
    QMatrix4x4 rescaleMatrix = QMatrix4x4(  scale,   0,       0,       0,
                                            0,       scale,   0,       0,
                                            0,       0,       scale,   0,
                                            0,       0,       0,       1);
    this->position = rescaleMatrix*this->position;
}

void MeshVertex::translate(QVector3D axis) {
    this->position += axis;
}

// rotation with a quaternion
void MeshVertex::rotate(QQuaternion rotationQuat) {
    this->position = rotationQuat*this->position;
}

// rotation with a quaternion going through a point
void MeshVertex::rotate(QQuaternion rotationQuat, QVector3D point) {
    this->position -= point;
    this->position = rotationQuat*this->position;
    this->position += point;
}

// rotation of angle degrees with an axis
void MeshVertex::rotate(float angle, QVector3D axis) {
    float radianToDegrees = 180/M_PI;
    QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(axis, angle*radianToDegrees);

    this->position = rotationQuat*this->position;
}

// rotation of angle degrees with an axis and going through a point
void MeshVertex::rotate(float angle, QVector3D axis, QVector3D point) {
    float radianToDegrees = 180/M_PI;
    QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(axis, angle*radianToDegrees);

    this->position -= point;
    this->position = rotationQuat*this->position;
    this->position += point;
}
