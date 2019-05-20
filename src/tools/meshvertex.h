#ifndef MESHVERTEX_H
#define MESHVERTEX_H

#include <QtMath>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QOpenGLFunctions>

class MeshVertex
{
public:
    MeshVertex();

    GLushort id;
    QVector3D position;
    QVector3D color;
    MeshVertex* top;
    MeshVertex* bottom;
    MeshVertex* right;
    MeshVertex* left;

    void computeNormalVector();
    void axisDeformation(QVector3D axis);
    void translation(QVector3D axis);
    void rotation(double angle, QVector3D axis, QVector3D point);
};

#endif // MESHVERTEX_H
