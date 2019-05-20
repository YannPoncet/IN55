#ifndef MESHVERTEX_H
#define MESHVERTEX_H

#include <QVector3D>
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
};

#endif // MESHVERTEX_H
