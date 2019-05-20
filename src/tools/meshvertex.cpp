#include "meshvertex.h"

MeshVertex::MeshVertex()
{

}

void MeshVertex::computeNormalVector() {

}

void MeshVertex::axisDeformation(QVector3D axis) {
    QMatrix4x4 deformation = QMatrix4x4(axis.x(),   0,          0,          0,
                                        0,          axis.y(),   0,          0,
                                        0,          0,          axis.z(),   0,
                                        0,          0,          0,          1);
    this->position = deformation*this->position;
}

void MeshVertex::translation(QVector3D axis) {
    this->position += axis;
}

// rotation of angle degrees with an axis and going through a point
void MeshVertex::rotation(double angle, QVector3D axis, QVector3D point) {
    QQuaternion rotationQuat = QQuaternion(cos(angle),axis*sin(angle));

    this->position -= point;
    this->position = rotationQuat*this->position;
    this->position += point;
}
