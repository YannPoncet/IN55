#ifndef CAP_H
#define CAP_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include "../tools/structs.h"

class Cap
{
public:
    Cap();
    QVector<VertexData> getVertices();
    QVector<GLushort> getIndices();
private:
    QVector<VertexData> vertices;
    QVector<GLushort> indices;
};

#endif // CAP_H
