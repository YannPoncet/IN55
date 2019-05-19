#ifndef STEM_H
#define STEM_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include "../tools/structs.h"

class Stem
{
public:
    Stem();
    QVector<VertexData> getVertices();
    QVector<GLushort> getIndices();
private:
    QVector<VertexData> vertices;
    QVector<GLushort> indices;
    QVector3D color;

    void generateBaseCylinder(double height, double radius);
};

#endif // STEM_H
