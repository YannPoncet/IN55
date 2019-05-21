#include "meshvertex.h"

MeshVertex::MeshVertex()
{

}

void MeshVertex::computeNormalVector() {

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

// rotation of angle degrees with an axis and going through a point
void MeshVertex::rotate(float angle, QVector3D axis, QVector3D point) {
    float radianToDegrees = 180/M_PI;
    QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(axis, angle*radianToDegrees);

    this->position -= point;
    this->position = rotationQuat*this->position;
    this->position += point;
}
