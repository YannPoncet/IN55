#ifndef STRUCT_H
#define STRUCT_H

#include <QVector3D>
#include <QOpenGLFunctions>

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

struct VerticesStruct
{
    VertexData* vertices;
    int nbrVertices;
};


struct IndicesStruct
{
    GLushort* indices;
    int nbrIndices;
};

#endif // STRUCT_H
